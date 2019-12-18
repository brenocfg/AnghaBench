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

/* Variables and functions */
#define  USB_RECIP_DEVICE 131 
#define  USB_RECIP_ENDPOINT 130 
#define  USB_RECIP_INTERFACE 129 
 int USB_RECIP_MASK ; 
#define  USB_RECIP_OTHER 128 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void usbip_dump_request_type(__u8 rt)
{
	switch (rt & USB_RECIP_MASK) {
	case USB_RECIP_DEVICE:
		pr_debug("DEVICE");
		break;
	case USB_RECIP_INTERFACE:
		pr_debug("INTERF");
		break;
	case USB_RECIP_ENDPOINT:
		pr_debug("ENDPOI");
		break;
	case USB_RECIP_OTHER:
		pr_debug("OTHER ");
		break;
	default:
		pr_debug("------");
		break;
	}
}