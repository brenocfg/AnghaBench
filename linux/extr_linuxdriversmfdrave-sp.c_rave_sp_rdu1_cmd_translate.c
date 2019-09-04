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
typedef  enum rave_sp_command { ____Placeholder_rave_sp_command } rave_sp_command ;

/* Variables and functions */
 int EINVAL ; 
 int RAVE_SP_CMD_CONTROL_EVENTS ; 
 int RAVE_SP_CMD_STATUS ; 

__attribute__((used)) static int rave_sp_rdu1_cmd_translate(enum rave_sp_command command)
{
	if (command >= RAVE_SP_CMD_STATUS &&
	    command <= RAVE_SP_CMD_CONTROL_EVENTS)
		return command;

	return -EINVAL;
}