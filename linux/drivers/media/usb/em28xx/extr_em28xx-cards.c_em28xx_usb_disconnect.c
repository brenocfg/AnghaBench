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
struct usb_interface {int dummy; } ;
struct em28xx {int disconnected; int /*<<< orphan*/  ref; struct em28xx* dev_next; int /*<<< orphan*/  name; TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_close_extension (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_free_device ; 
 int /*<<< orphan*/  em28xx_release_resources (struct em28xx*) ; 
 int /*<<< orphan*/  flush_request_modules (struct em28xx*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct em28xx* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void em28xx_usb_disconnect(struct usb_interface *intf)
{
	struct em28xx *dev;

	dev = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NULL);

	if (!dev)
		return;

	if (dev->dev_next) {
		dev->dev_next->disconnected = 1;
		dev_info(&dev->intf->dev, "Disconnecting %s\n",
			 dev->dev_next->name);
	}

	dev->disconnected = 1;

	dev_info(&dev->intf->dev, "Disconnecting %s\n", dev->name);

	flush_request_modules(dev);

	em28xx_close_extension(dev);

	if (dev->dev_next)
		em28xx_release_resources(dev->dev_next);
	em28xx_release_resources(dev);

	if (dev->dev_next) {
		kref_put(&dev->dev_next->ref, em28xx_free_device);
		dev->dev_next = NULL;
	}
	kref_put(&dev->ref, em28xx_free_device);
}