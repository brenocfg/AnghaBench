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
#define  WMI_CHANNEL_1 137 
#define  WMI_CHANNEL_10 136 
#define  WMI_CHANNEL_11 135 
#define  WMI_CHANNEL_12 134 
#define  WMI_CHANNEL_2 133 
#define  WMI_CHANNEL_3 132 
#define  WMI_CHANNEL_4 131 
#define  WMI_CHANNEL_5 130 
#define  WMI_CHANNEL_6 129 
#define  WMI_CHANNEL_9 128 

int wil_wmi2spec_ch(u8 wmi_ch, u8 *spec_ch)
{
	switch (wmi_ch) {
	case WMI_CHANNEL_1:
		*spec_ch = 1;
		break;
	case WMI_CHANNEL_2:
		*spec_ch = 2;
		break;
	case WMI_CHANNEL_3:
		*spec_ch = 3;
		break;
	case WMI_CHANNEL_4:
		*spec_ch = 4;
		break;
	case WMI_CHANNEL_5:
		*spec_ch = 5;
		break;
	case WMI_CHANNEL_6:
		*spec_ch = 6;
		break;
	case WMI_CHANNEL_9:
		*spec_ch = 9;
		break;
	case WMI_CHANNEL_10:
		*spec_ch = 10;
		break;
	case WMI_CHANNEL_11:
		*spec_ch = 11;
		break;
	case WMI_CHANNEL_12:
		*spec_ch = 12;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}