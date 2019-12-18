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
 int RAVE_SP_CMD_GET_FIRMWARE_VERSION ; 
 int RAVE_SP_CMD_GET_GPIO_STATE ; 
 int RAVE_SP_CMD_REQ_COPPER_REV ; 
 int rave_sp_rdu1_cmd_translate (int) ; 

__attribute__((used)) static int rave_sp_rdu2_cmd_translate(enum rave_sp_command command)
{
	if (command >= RAVE_SP_CMD_GET_FIRMWARE_VERSION &&
	    command <= RAVE_SP_CMD_GET_GPIO_STATE)
		return command;

	if (command == RAVE_SP_CMD_REQ_COPPER_REV) {
		/*
		 * As per RDU2 ICD 3.4.47 CMD_GET_COPPER_REV code is
		 * different from that for RDU1 and it is set to 0x28.
		 */
		return 0x28;
	}

	return rave_sp_rdu1_cmd_translate(command);
}