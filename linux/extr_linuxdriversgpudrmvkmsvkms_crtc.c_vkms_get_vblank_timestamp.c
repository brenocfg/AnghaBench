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
struct TYPE_3__ {int /*<<< orphan*/  expires; } ;
struct TYPE_4__ {TYPE_1__ node; } ;
struct vkms_output {scalar_t__ period_ns; TYPE_2__ vblank_hrtimer; } ;
struct vkms_device {struct vkms_output output; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 struct vkms_device* drm_device_to_vkms_device (struct drm_device*) ; 

bool vkms_get_vblank_timestamp(struct drm_device *dev, unsigned int pipe,
			       int *max_error, ktime_t *vblank_time,
			       bool in_vblank_irq)
{
	struct vkms_device *vkmsdev = drm_device_to_vkms_device(dev);
	struct vkms_output *output = &vkmsdev->output;

	*vblank_time = output->vblank_hrtimer.node.expires;

	if (!in_vblank_irq)
		*vblank_time -= output->period_ns;

	return true;
}