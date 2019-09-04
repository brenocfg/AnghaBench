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

/* Variables and functions */
 int /*<<< orphan*/  LINUX_REBOOT_CMD_RESTART ; 
 int /*<<< orphan*/  common_shutdown (int /*<<< orphan*/ ,char*) ; 

void
machine_restart(char *restart_cmd)
{
	common_shutdown(LINUX_REBOOT_CMD_RESTART, restart_cmd);
}