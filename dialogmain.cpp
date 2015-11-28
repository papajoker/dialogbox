/*
 * GUI widgets for shell scripts - dialogbox version 0.8
 *
 * Copyright (C) 2015 Andriy Martynets <martynets@volia.ua>
 *--------------------------------------------------------------------------------------------------------------
 * This file is part of dialogbox.
 *
 * Dialogbox is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * Dialogbox is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with dialogbox.
 * If not, see http://www.gnu.org/licenses/.
 *--------------------------------------------------------------------------------------------------------------
 */

#include <unistd.h>
#include <QApplication>
#include "dialogbox.hpp"

/*	EXIT CODES */
#define E_SUCCESS	0
#define E_ARG		1

#define PROGRAM_NAME "dialogbox"
#define VERSION "0.8"

static char* about_message=
PROGRAM_NAME" v"VERSION"\n\
Copyright (C) 2015 Andriy Martynets <martynets@volia.ua>\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n\
This program comes with ABSOLUTELY NO WARRANTY.\n\
This is free software, and you are welcome to redistribute it\n\
under certain conditions. See the GNU GPL for details.\n\n\
More information on <https://github.com/martynets/dialogbox/>.\n";

static char* about_html_message=
"<h3>"PROGRAM_NAME" version "VERSION"</h3>\
<p><b>Copyright (C) 2015 Andriy Martynets </b><a href=\"mailto:martynets@volia.ua\">martynets@volia.ua</a></p>\
<p><b>License GPLv3+:</b> GNU GPL version 3 or later <a href=\"http://gnu.org/licenses/gpl.html\">http://gnu.org/licenses/gpl.html</a>.</p>\
<p>This program comes with ABSOLUTELY NO WARRANTY. \
This is free software, and you are welcome to redistribute it \
under certain conditions. See the GNU GPL for details.</p>\
<p>More information on <a href=\"https://github.com/martynets/dialogbox/\">https://github.com/martynets/dialogbox/</a>.</p>";

static char* default_title=PROGRAM_NAME" v"VERSION;

static void help();
static void version();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DialogBox dialog(default_title,about_html_message);
    DialogParser parser(&dialog);

	// Consider QApplication has removed everything it recognized...
	for(int i=1; i<argc; i++)
		{
			if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
				{
					help();
					return(E_SUCCESS);
				}
			if(!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version"))
				{
					version();
					return(E_SUCCESS);
				}
			fprintf(stderr,"Error: Unrecognized option %s\n", argv[i]);
			return(E_ARG);
		}

	parser.start();
    return(dialog.exec());
}

static void version()
{
	puts(about_message);
}

static void help()
{
	char* usage=
"Usage:	"PROGRAM_NAME" [OPTION]\n\
Translate commands on stdin into widgets of GUI dialogbox and output user\n\
actions to stdout.\n\
\n\
Option could be:\n\
	-h, --help	display this help and exit\n\
	-v, --version	output version information and exit\n\
\n\
Supported commands:\n\
	- add type title [name] [options] [text] [auxtext]\n\
	- end [type]\n\
	- step [options]\n\
	- set [name] options [text]\n\
	- unset [name] options\n\
	- enable [name]\n\
	- disable [name]\n\
	- remove name\n\
	- print\n\
	- position options name (behind | onto)\n\
Output format:\n\
	- on pushbutton click:\n\
		<pushbutton name>=clicked\n\
	- additionally if apply option is set list all named widgets in format:\n\
		<name>=<value>\n\
\n\
Full documentation at: <https://github.com/martynets/dialogbox/>\n";

	puts(usage);
}
