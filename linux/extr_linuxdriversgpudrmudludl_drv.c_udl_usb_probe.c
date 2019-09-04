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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct drm_device {TYPE_1__* primary; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int /*<<< orphan*/  driver ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_dev_register (struct drm_device*,unsigned long) ; 
 int /*<<< orphan*/  drm_dev_unref (struct drm_device*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct drm_device*) ; 

__attribute__((used)) static int udl_usb_probe(struct usb_interface *interface,
			 const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct drm_device *dev;
	int r;

	dev = drm_dev_alloc(&driver, &interface->dev);
	if (IS_ERR(dev))
		return PTR_ERR(dev);

	r = drm_dev_register(dev, (unsigned long)udev);
	if (r)
		goto err_free;

	usb_set_intfdata(interface, dev);
	DRM_INFO("Initialized udl on minor %d\n", dev->primary->index);

	return 0;

err_free:
	drm_dev_unref(dev);
	return r;
}