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
#define  DEV_OPMODE_AP_BT 136 
#define  DEV_OPMODE_AP_BT_DUAL 135 
#define  DEV_OPMODE_BT_ALONE 134 
#define  DEV_OPMODE_BT_DUAL 133 
#define  DEV_OPMODE_BT_LE_ALONE 132 
#define  DEV_OPMODE_STA_BT 131 
#define  DEV_OPMODE_STA_BT_DUAL 130 
#define  DEV_OPMODE_STA_BT_LE 129 
#define  DEV_OPMODE_WIFI_ALONE 128 

__attribute__((used)) static char *opmode_str(int oper_mode)
{
	switch (oper_mode) {
	case DEV_OPMODE_WIFI_ALONE:
		return "Wi-Fi alone";
	case DEV_OPMODE_BT_ALONE:
		return "BT EDR alone";
	case DEV_OPMODE_BT_LE_ALONE:
		return "BT LE alone";
	case DEV_OPMODE_BT_DUAL:
		return "BT Dual";
	case DEV_OPMODE_STA_BT:
		return "Wi-Fi STA + BT EDR";
	case DEV_OPMODE_STA_BT_LE:
		return "Wi-Fi STA + BT LE";
	case DEV_OPMODE_STA_BT_DUAL:
		return "Wi-Fi STA + BT DUAL";
	case DEV_OPMODE_AP_BT:
		return "Wi-Fi AP + BT EDR";
	case DEV_OPMODE_AP_BT_DUAL:
		return "Wi-Fi AP + BT DUAL";
	}

	return "Unknown";
}