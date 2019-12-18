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
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
#define  USB_REQ_CLEAR_FEATURE 140 
#define  USB_REQ_GET_CONFIGURATION 139 
#define  USB_REQ_GET_DESCRIPTOR 138 
#define  USB_REQ_GET_INTERFACE 137 
#define  USB_REQ_GET_STATUS 136 
#define  USB_REQ_SET_ADDRESS 135 
#define  USB_REQ_SET_CONFIGURATION 134 
#define  USB_REQ_SET_DESCRIPTOR 133 
#define  USB_REQ_SET_FEATURE 132 
#define  USB_REQ_SET_INTERFACE 131 
#define  USB_REQ_SET_ISOCH_DELAY 130 
#define  USB_REQ_SET_SEL 129 
#define  USB_REQ_SYNCH_FRAME 128 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  usb_decode_get_configuration (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  usb_decode_get_intf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  usb_decode_get_set_descriptor (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  usb_decode_get_status (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  usb_decode_set_address (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  usb_decode_set_clear_feature (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  usb_decode_set_configuration (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  usb_decode_set_intf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  usb_decode_set_isoch_delay (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  usb_decode_set_sel (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  usb_decode_synch_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 

const char *usb_decode_ctrl(char *str, size_t size, __u8 bRequestType,
			    __u8 bRequest, __u16 wValue, __u16 wIndex,
			    __u16 wLength)
{
	switch (bRequest) {
	case USB_REQ_GET_STATUS:
		usb_decode_get_status(bRequestType, wIndex, wLength, str, size);
		break;
	case USB_REQ_CLEAR_FEATURE:
	case USB_REQ_SET_FEATURE:
		usb_decode_set_clear_feature(bRequestType, bRequest, wValue,
					     wIndex, str, size);
		break;
	case USB_REQ_SET_ADDRESS:
		usb_decode_set_address(wValue, str, size);
		break;
	case USB_REQ_GET_DESCRIPTOR:
	case USB_REQ_SET_DESCRIPTOR:
		usb_decode_get_set_descriptor(bRequestType, bRequest, wValue,
					      wIndex, wLength, str, size);
		break;
	case USB_REQ_GET_CONFIGURATION:
		usb_decode_get_configuration(wLength, str, size);
		break;
	case USB_REQ_SET_CONFIGURATION:
		usb_decode_set_configuration(wValue, str, size);
		break;
	case USB_REQ_GET_INTERFACE:
		usb_decode_get_intf(wIndex, wLength, str, size);
		break;
	case USB_REQ_SET_INTERFACE:
		usb_decode_set_intf(wValue, wIndex, str, size);
		break;
	case USB_REQ_SYNCH_FRAME:
		usb_decode_synch_frame(wIndex, wLength, str, size);
		break;
	case USB_REQ_SET_SEL:
		usb_decode_set_sel(wLength, str, size);
		break;
	case USB_REQ_SET_ISOCH_DELAY:
		usb_decode_set_isoch_delay(wValue, str, size);
		break;
	default:
		snprintf(str, size, "%02x %02x %02x %02x %02x %02x %02x %02x",
			 bRequestType, bRequest,
			 (u8)(cpu_to_le16(wValue) & 0xff),
			 (u8)(cpu_to_le16(wValue) >> 8),
			 (u8)(cpu_to_le16(wIndex) & 0xff),
			 (u8)(cpu_to_le16(wIndex) >> 8),
			 (u8)(cpu_to_le16(wLength) & 0xff),
			 (u8)(cpu_to_le16(wLength) >> 8));
	}

	return str;
}