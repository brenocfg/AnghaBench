#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_5__ {TYPE_1__* primary; } ;
struct udl_device {TYPE_2__ drm; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct udl_device*) ; 
 int PTR_ERR (struct udl_device*) ; 
 int /*<<< orphan*/  drm_dev_put (TYPE_2__*) ; 
 int drm_dev_register (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct udl_device* udl_driver_create (struct usb_interface*) ; 

__attribute__((used)) static int udl_usb_probe(struct usb_interface *interface,
			 const struct usb_device_id *id)
{
	int r;
	struct udl_device *udl;

	udl = udl_driver_create(interface);
	if (IS_ERR(udl))
		return PTR_ERR(udl);

	r = drm_dev_register(&udl->drm, 0);
	if (r)
		goto err_free;

	DRM_INFO("Initialized udl on minor %d\n", udl->drm.primary->index);

	return 0;

err_free:
	drm_dev_put(&udl->drm);
	return r;
}