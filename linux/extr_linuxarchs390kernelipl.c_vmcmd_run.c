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
struct shutdown_trigger {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ON_HALT_STR ; 
 int /*<<< orphan*/  ON_PANIC_STR ; 
 int /*<<< orphan*/  ON_POFF_STR ; 
 int /*<<< orphan*/  ON_REIPL_STR ; 
 int /*<<< orphan*/  ON_RESTART_STR ; 
 int /*<<< orphan*/  __cpcmd (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 char* vmcmd_on_halt ; 
 char* vmcmd_on_panic ; 
 char* vmcmd_on_poff ; 
 char* vmcmd_on_reboot ; 
 char* vmcmd_on_restart ; 

__attribute__((used)) static void vmcmd_run(struct shutdown_trigger *trigger)
{
	char *cmd;

	if (strcmp(trigger->name, ON_REIPL_STR) == 0)
		cmd = vmcmd_on_reboot;
	else if (strcmp(trigger->name, ON_PANIC_STR) == 0)
		cmd = vmcmd_on_panic;
	else if (strcmp(trigger->name, ON_HALT_STR) == 0)
		cmd = vmcmd_on_halt;
	else if (strcmp(trigger->name, ON_POFF_STR) == 0)
		cmd = vmcmd_on_poff;
	else if (strcmp(trigger->name, ON_RESTART_STR) == 0)
		cmd = vmcmd_on_restart;
	else
		return;

	if (strlen(cmd) == 0)
		return;
	__cpcmd(cmd, NULL, 0, NULL);
}