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
#define  FIT_SR_DRIVE_BUSY 140 
#define  FIT_SR_DRIVE_BUSY_ERASE 139 
#define  FIT_SR_DRIVE_BUSY_SANITIZE 138 
#define  FIT_SR_DRIVE_DEGRADED 137 
#define  FIT_SR_DRIVE_FAULT 136 
#define  FIT_SR_DRIVE_FW_BOOTING 135 
#define  FIT_SR_DRIVE_INIT 134 
#define  FIT_SR_DRIVE_INIT_FAULT 133 
#define  FIT_SR_DRIVE_NEED_FW_DOWNLOAD 132 
#define  FIT_SR_DRIVE_OFFLINE 131 
#define  FIT_SR_DRIVE_ONLINE 130 
#define  FIT_SR_DRIVE_SOFT_RESET 129 
#define  FIT_SR_PCIE_LINK_DOWN 128 

const char *skd_drive_state_to_str(int state)
{
	switch (state) {
	case FIT_SR_DRIVE_OFFLINE:
		return "OFFLINE";
	case FIT_SR_DRIVE_INIT:
		return "INIT";
	case FIT_SR_DRIVE_ONLINE:
		return "ONLINE";
	case FIT_SR_DRIVE_BUSY:
		return "BUSY";
	case FIT_SR_DRIVE_FAULT:
		return "FAULT";
	case FIT_SR_DRIVE_DEGRADED:
		return "DEGRADED";
	case FIT_SR_PCIE_LINK_DOWN:
		return "INK_DOWN";
	case FIT_SR_DRIVE_SOFT_RESET:
		return "SOFT_RESET";
	case FIT_SR_DRIVE_NEED_FW_DOWNLOAD:
		return "NEED_FW";
	case FIT_SR_DRIVE_INIT_FAULT:
		return "INIT_FAULT";
	case FIT_SR_DRIVE_BUSY_SANITIZE:
		return "BUSY_SANITIZE";
	case FIT_SR_DRIVE_BUSY_ERASE:
		return "BUSY_ERASE";
	case FIT_SR_DRIVE_FW_BOOTING:
		return "FW_BOOTING";
	default:
		return "???";
	}
}