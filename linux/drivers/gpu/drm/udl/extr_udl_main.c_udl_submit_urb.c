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
struct urb {size_t transfer_buffer_length; } ;
struct TYPE_2__ {size_t size; } ;
struct udl_device {int /*<<< orphan*/  lost_pixels; TYPE_1__ urbs; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct udl_device* to_udl (struct drm_device*) ; 
 int /*<<< orphan*/  udl_urb_completion (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

int udl_submit_urb(struct drm_device *dev, struct urb *urb, size_t len)
{
	struct udl_device *udl = to_udl(dev);
	int ret;

	BUG_ON(len > udl->urbs.size);

	urb->transfer_buffer_length = len; /* set to actual payload len */
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	if (ret) {
		udl_urb_completion(urb); /* because no one else will */
		atomic_set(&udl->lost_pixels, 1);
		DRM_ERROR("usb_submit_urb error %x\n", ret);
	}
	return ret;
}