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
struct usb_interface {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unplug (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int /*<<< orphan*/  udl_drop_usb (struct drm_device*) ; 
 int /*<<< orphan*/  udl_fbdev_unplug (struct drm_device*) ; 
 struct drm_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void udl_usb_disconnect(struct usb_interface *interface)
{
	struct drm_device *dev = usb_get_intfdata(interface);

	drm_kms_helper_poll_disable(dev);
	udl_fbdev_unplug(dev);
	udl_drop_usb(dev);
	drm_dev_unplug(dev);
	drm_dev_put(dev);
}