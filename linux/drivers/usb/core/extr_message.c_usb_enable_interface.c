#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_2__ {int bNumEndpoints; } ;
struct usb_host_interface {int /*<<< orphan*/ * endpoint; TYPE_1__ desc; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_enable_endpoint (struct usb_device*,int /*<<< orphan*/ *,int) ; 

void usb_enable_interface(struct usb_device *dev,
		struct usb_interface *intf, bool reset_eps)
{
	struct usb_host_interface *alt = intf->cur_altsetting;
	int i;

	for (i = 0; i < alt->desc.bNumEndpoints; ++i)
		usb_enable_endpoint(dev, &alt->endpoint[i], reset_eps);
}