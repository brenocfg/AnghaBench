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
struct ep_device {int /*<<< orphan*/  desc; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct ep_device* to_ep_device (struct device*) ; 
 int usb_endpoint_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t type_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct ep_device *ep = to_ep_device(dev);
	char *type = "unknown";

	switch (usb_endpoint_type(ep->desc)) {
	case USB_ENDPOINT_XFER_CONTROL:
		type = "Control";
		break;
	case USB_ENDPOINT_XFER_ISOC:
		type = "Isoc";
		break;
	case USB_ENDPOINT_XFER_BULK:
		type = "Bulk";
		break;
	case USB_ENDPOINT_XFER_INT:
		type = "Interrupt";
		break;
	}
	return sprintf(buf, "%s\n", type);
}