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
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int USB_DIR_IN ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,...) ; 

__attribute__((used)) static void usb_decode_get_status(__u8 bRequestType, __u16 wIndex,
				  __u16 wLength, char *str, size_t size)
{
	switch (bRequestType & USB_RECIP_MASK) {
	case USB_RECIP_DEVICE:
		snprintf(str, size, "Get Device Status(Length = %d)", wLength);
		break;
	case USB_RECIP_INTERFACE:
		snprintf(str, size,
			 "Get Interface Status(Intf = %d, Length = %d)",
			 wIndex, wLength);
		break;
	case USB_RECIP_ENDPOINT:
		snprintf(str, size, "Get Endpoint Status(ep%d%s)",
			 wIndex & ~USB_DIR_IN,
			 wIndex & USB_DIR_IN ? "in" : "out");
		break;
	}
}