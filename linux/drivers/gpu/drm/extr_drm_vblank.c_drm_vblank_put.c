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
struct drm_vblank_crtc {int /*<<< orphan*/  disable_timer; int /*<<< orphan*/  refcount; } ;
struct drm_device {unsigned int num_crtcs; int /*<<< orphan*/  vblank_disable_immediate; struct drm_vblank_crtc* vblank; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int drm_vblank_offdelay ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vblank_disable_fn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_vblank_put(struct drm_device *dev, unsigned int pipe)
{
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];

	if (WARN_ON(pipe >= dev->num_crtcs))
		return;

	if (WARN_ON(atomic_read(&vblank->refcount) == 0))
		return;

	/* Last user schedules interrupt disable */
	if (atomic_dec_and_test(&vblank->refcount)) {
		if (drm_vblank_offdelay == 0)
			return;
		else if (drm_vblank_offdelay < 0)
			vblank_disable_fn(&vblank->disable_timer);
		else if (!dev->vblank_disable_immediate)
			mod_timer(&vblank->disable_timer,
				  jiffies + ((drm_vblank_offdelay * HZ)/1000));
	}
}