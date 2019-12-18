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
 int /*<<< orphan*/  CMD_ISA_SWITCH_SETTINGS ; 
 int send_isa_command (int /*<<< orphan*/ ) ; 
 scalar_t__ set_command_mode () ; 
 int /*<<< orphan*/  unset_command_mode () ; 

__attribute__((used)) static inline int pcwd_get_option_switches(void)
{
	int option_switches = 0;

	if (set_command_mode()) {
		/* Get switch settings */
		option_switches = send_isa_command(CMD_ISA_SWITCH_SETTINGS);
	}

	unset_command_mode();
	return option_switches;
}