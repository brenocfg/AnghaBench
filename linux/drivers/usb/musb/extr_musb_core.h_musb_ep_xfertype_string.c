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
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 

__attribute__((used)) static inline char *musb_ep_xfertype_string(u8 type)
{
	char *s;

	switch (type) {
	case USB_ENDPOINT_XFER_CONTROL:
		s = "ctrl";
		break;
	case USB_ENDPOINT_XFER_ISOC:
		s = "iso";
		break;
	case USB_ENDPOINT_XFER_BULK:
		s = "bulk";
		break;
	case USB_ENDPOINT_XFER_INT:
		s = "int";
		break;
	default:
		s = "";
		break;
	}
	return s;
}