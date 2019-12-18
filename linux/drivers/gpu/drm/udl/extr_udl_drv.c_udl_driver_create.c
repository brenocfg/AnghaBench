#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device {int dummy; } ;
struct TYPE_3__ {struct udl_device* dev_private; } ;
struct udl_device {TYPE_1__ drm; struct usb_device* udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct udl_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  driver ; 
 int /*<<< orphan*/  drm_dev_fini (TYPE_1__*) ; 
 int drm_dev_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct udl_device*) ; 
 struct udl_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int udl_init (struct udl_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct udl_device*) ; 

__attribute__((used)) static struct udl_device *udl_driver_create(struct usb_interface *interface)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct udl_device *udl;
	int r;

	udl = kzalloc(sizeof(*udl), GFP_KERNEL);
	if (!udl)
		return ERR_PTR(-ENOMEM);

	r = drm_dev_init(&udl->drm, &driver, &interface->dev);
	if (r) {
		kfree(udl);
		return ERR_PTR(r);
	}

	udl->udev = udev;
	udl->drm.dev_private = udl;

	r = udl_init(udl);
	if (r) {
		drm_dev_fini(&udl->drm);
		kfree(udl);
		return ERR_PTR(r);
	}

	usb_set_intfdata(interface, udl);
	return udl;
}