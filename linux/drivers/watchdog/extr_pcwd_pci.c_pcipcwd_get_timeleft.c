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
 int /*<<< orphan*/  CMD_READ_WATCHDOG_TIMEOUT ; 
 scalar_t__ VERBOSE ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  send_command (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int pcipcwd_get_timeleft(int *time_left)
{
	int msb;
	int lsb;

	/* Read the time that's left before rebooting */
	/* Note: if the board is not yet armed then we will read 0xFFFF */
	send_command(CMD_READ_WATCHDOG_TIMEOUT, &msb, &lsb);

	*time_left = (msb << 8) + lsb;

	if (debug >= VERBOSE)
		pr_debug("Time left before next reboot: %d\n", *time_left);

	return 0;
}