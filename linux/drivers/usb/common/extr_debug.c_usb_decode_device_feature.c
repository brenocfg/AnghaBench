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
typedef  int u16 ;

/* Variables and functions */
#define  USB_DEVICE_LTM_ENABLE 133 
#define  USB_DEVICE_REMOTE_WAKEUP 132 
#define  USB_DEVICE_SELF_POWERED 131 
#define  USB_DEVICE_TEST_MODE 130 
#define  USB_DEVICE_U1_ENABLE 129 
#define  USB_DEVICE_U2_ENABLE 128 

__attribute__((used)) static const char *usb_decode_device_feature(u16 wValue)
{
	switch (wValue) {
	case USB_DEVICE_SELF_POWERED:
		return "Self Powered";
	case USB_DEVICE_REMOTE_WAKEUP:
		return "Remote Wakeup";
	case USB_DEVICE_TEST_MODE:
		return "Test Mode";
	case USB_DEVICE_U1_ENABLE:
		return "U1 Enable";
	case USB_DEVICE_U2_ENABLE:
		return "U2 Enable";
	case USB_DEVICE_LTM_ENABLE:
		return "LTM Enable";
	default:
		return "UNKNOWN";
	}
}