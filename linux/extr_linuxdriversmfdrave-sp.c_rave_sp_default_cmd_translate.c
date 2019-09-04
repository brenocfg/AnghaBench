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
#define  RAVE_SP_CMD_BOOT_SOURCE 135 
#define  RAVE_SP_CMD_GET_BOOTLOADER_VERSION 134 
#define  RAVE_SP_CMD_GET_FIRMWARE_VERSION 133 
#define  RAVE_SP_CMD_PET_WDT 132 
#define  RAVE_SP_CMD_RESET 131 
#define  RAVE_SP_CMD_RESET_REASON 130 
#define  RAVE_SP_CMD_RMB_EEPROM 129 
#define  RAVE_SP_CMD_SW_WDT 128 

__attribute__((used)) static int rave_sp_default_cmd_translate(enum rave_sp_command command)
{
	/*
	 * All of the following command codes were taken from "Table :
	 * Communications Protocol Message Types" in section 3.3
	 * "MESSAGE TYPES" of Rave PIC24 ICD.
	 */
	switch (command) {
	case RAVE_SP_CMD_GET_FIRMWARE_VERSION:
		return 0x11;
	case RAVE_SP_CMD_GET_BOOTLOADER_VERSION:
		return 0x12;
	case RAVE_SP_CMD_BOOT_SOURCE:
		return 0x14;
	case RAVE_SP_CMD_SW_WDT:
		return 0x1C;
	case RAVE_SP_CMD_PET_WDT:
		return 0x1D;
	case RAVE_SP_CMD_RESET:
		return 0x1E;
	case RAVE_SP_CMD_RESET_REASON:
		return 0x1F;
	case RAVE_SP_CMD_RMB_EEPROM:
		return 0x20;
	default:
		return -EINVAL;
	}
}