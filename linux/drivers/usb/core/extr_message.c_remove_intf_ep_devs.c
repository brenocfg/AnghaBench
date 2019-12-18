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
struct usb_interface {scalar_t__ ep_devs_created; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_2__ {int bNumEndpoints; } ;
struct usb_host_interface {int /*<<< orphan*/ * endpoint; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_remove_ep_devs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_intf_ep_devs(struct usb_interface *intf)
{
	struct usb_host_interface *alt = intf->cur_altsetting;
	int i;

	if (!intf->ep_devs_created)
		return;

	for (i = 0; i < alt->desc.bNumEndpoints; ++i)
		usb_remove_ep_devs(&alt->endpoint[i]);
	intf->ep_devs_created = 0;
}