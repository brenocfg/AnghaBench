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
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 
 int /*<<< orphan*/  udl_modeset_restore (struct drm_device*) ; 
 struct drm_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int udl_usb_resume(struct usb_interface *interface)
{
	struct drm_device *dev = usb_get_intfdata(interface);

	drm_kms_helper_poll_enable(dev);
	udl_modeset_restore(dev);
	return 0;
}