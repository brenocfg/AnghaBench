#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;
struct TYPE_3__ {TYPE_2__ node; } ;
struct vkms_output {scalar_t__ period_ns; TYPE_1__ vblank_hrtimer; } ;
struct vkms_device {struct vkms_output output; } ;
struct drm_vblank_crtc {scalar_t__ time; } ;
struct drm_device {struct drm_vblank_crtc* vblank; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct vkms_device* drm_device_to_vkms_device (struct drm_device*) ; 

bool vkms_get_vblank_timestamp(struct drm_device *dev, unsigned int pipe,
			       int *max_error, ktime_t *vblank_time,
			       bool in_vblank_irq)
{
	struct vkms_device *vkmsdev = drm_device_to_vkms_device(dev);
	struct vkms_output *output = &vkmsdev->output;
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];

	*vblank_time = output->vblank_hrtimer.node.expires;

	if (WARN_ON(*vblank_time == vblank->time))
		return true;

	/*
	 * To prevent races we roll the hrtimer forward before we do any
	 * interrupt processing - this is how real hw works (the interrupt is
	 * only generated after all the vblank registers are updated) and what
	 * the vblank core expects. Therefore we need to always correct the
	 * timestampe by one frame.
	 */
	*vblank_time -= output->period_ns;

	return true;
}