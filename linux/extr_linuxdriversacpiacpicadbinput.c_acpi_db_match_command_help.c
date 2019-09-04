#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct acpi_db_command_help {char* invocation; int /*<<< orphan*/  description; scalar_t__ line_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_os_printf (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tolower (int) ; 

__attribute__((used)) static u8
acpi_db_match_command_help(const char *command,
			   const struct acpi_db_command_help *help)
{
	char *invocation = help->invocation;
	u32 line_count;

	/* Valid commands in the help table begin with a couple of spaces */

	if (*invocation != ' ') {
		return (FALSE);
	}

	while (*invocation == ' ') {
		invocation++;
	}

	/* Match command name (full command or substring) */

	while ((*command) && (*invocation) && (*invocation != ' ')) {
		if (tolower((int)*command) != tolower((int)*invocation)) {
			return (FALSE);
		}

		invocation++;
		command++;
	}

	/* Print the appropriate number of help lines */

	line_count = help->line_count;
	while (line_count) {
		acpi_os_printf("%-38s : %s", help->invocation,
			       help->description);
		help++;
		line_count--;
	}

	return (TRUE);
}