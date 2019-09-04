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
#define  USB_CHG_TYPE_BC12_CDP 137 
#define  USB_CHG_TYPE_BC12_DCP 136 
#define  USB_CHG_TYPE_BC12_SDP 135 
#define  USB_CHG_TYPE_C 134 
#define  USB_CHG_TYPE_NONE 133 
#define  USB_CHG_TYPE_OTHER 132 
#define  USB_CHG_TYPE_PD 131 
#define  USB_CHG_TYPE_PROPRIETARY 130 
#define  USB_CHG_TYPE_UNKNOWN 129 
#define  USB_CHG_TYPE_VBUS 128 

__attribute__((used)) static const char *cros_ec_usb_power_type_string(unsigned int type)
{
	switch (type) {
	case USB_CHG_TYPE_NONE:
		return "USB_CHG_TYPE_NONE";
	case USB_CHG_TYPE_PD:
		return "USB_CHG_TYPE_PD";
	case USB_CHG_TYPE_PROPRIETARY:
		return "USB_CHG_TYPE_PROPRIETARY";
	case USB_CHG_TYPE_C:
		return "USB_CHG_TYPE_C";
	case USB_CHG_TYPE_BC12_DCP:
		return "USB_CHG_TYPE_BC12_DCP";
	case USB_CHG_TYPE_BC12_CDP:
		return "USB_CHG_TYPE_BC12_CDP";
	case USB_CHG_TYPE_BC12_SDP:
		return "USB_CHG_TYPE_BC12_SDP";
	case USB_CHG_TYPE_OTHER:
		return "USB_CHG_TYPE_OTHER";
	case USB_CHG_TYPE_VBUS:
		return "USB_CHG_TYPE_VBUS";
	case USB_CHG_TYPE_UNKNOWN:
		return "USB_CHG_TYPE_UNKNOWN";
	default:
		return "USB_CHG_TYPE_UNKNOWN";
	}
}