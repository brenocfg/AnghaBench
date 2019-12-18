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
typedef  int u8 ;

/* Variables and functions */
 int EINVAL ; 
 int WMI_CHANNEL_1 ; 
 int WMI_CHANNEL_10 ; 
 int WMI_CHANNEL_11 ; 
 int WMI_CHANNEL_12 ; 
 int WMI_CHANNEL_2 ; 
 int WMI_CHANNEL_3 ; 
 int WMI_CHANNEL_4 ; 
 int WMI_CHANNEL_5 ; 
 int WMI_CHANNEL_6 ; 
 int WMI_CHANNEL_9 ; 

int wil_spec2wmi_ch(u8 spec_ch, u8 *wmi_ch)
{
	switch (spec_ch) {
	case 1:
		*wmi_ch = WMI_CHANNEL_1;
		break;
	case 2:
		*wmi_ch = WMI_CHANNEL_2;
		break;
	case 3:
		*wmi_ch = WMI_CHANNEL_3;
		break;
	case 4:
		*wmi_ch = WMI_CHANNEL_4;
		break;
	case 5:
		*wmi_ch = WMI_CHANNEL_5;
		break;
	case 6:
		*wmi_ch = WMI_CHANNEL_6;
		break;
	case 9:
		*wmi_ch = WMI_CHANNEL_9;
		break;
	case 10:
		*wmi_ch = WMI_CHANNEL_10;
		break;
	case 11:
		*wmi_ch = WMI_CHANNEL_11;
		break;
	case 12:
		*wmi_ch = WMI_CHANNEL_12;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}