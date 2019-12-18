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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct gs_usb {int /*<<< orphan*/  rx_submitted; scalar_t__* canch; } ;

/* Variables and functions */
 unsigned int GS_MAX_INTF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_destroy_candev (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct gs_usb*) ; 
 struct gs_usb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gs_usb_disconnect(struct usb_interface *intf)
{
	unsigned i;
	struct gs_usb *dev = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NULL);

	if (!dev) {
		dev_err(&intf->dev, "Disconnect (nodata)\n");
		return;
	}

	for (i = 0; i < GS_MAX_INTF; i++)
		if (dev->canch[i])
			gs_destroy_candev(dev->canch[i]);

	usb_kill_anchored_urbs(&dev->rx_submitted);
	kfree(dev);
}