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
typedef  enum fw_status { ____Placeholder_fw_status } fw_status ;

/* Variables and functions */
#define  FW_STATUS_INIT 131 
#define  FW_STATUS_LOAD_DMEM 130 
#define  FW_STATUS_LOAD_EMEM 129 
#define  FW_STATUS_LOAD_IMEM 128 
 int FW_STATUS_READY ; 

__attribute__((used)) static enum fw_status _rtl92s_firmware_get_nextstatus(
		enum fw_status fw_currentstatus)
{
	enum fw_status	next_fwstatus = 0;

	switch (fw_currentstatus) {
	case FW_STATUS_INIT:
		next_fwstatus = FW_STATUS_LOAD_IMEM;
		break;
	case FW_STATUS_LOAD_IMEM:
		next_fwstatus = FW_STATUS_LOAD_EMEM;
		break;
	case FW_STATUS_LOAD_EMEM:
		next_fwstatus = FW_STATUS_LOAD_DMEM;
		break;
	case FW_STATUS_LOAD_DMEM:
		next_fwstatus = FW_STATUS_READY;
		break;
	default:
		break;
	}

	return next_fwstatus;
}