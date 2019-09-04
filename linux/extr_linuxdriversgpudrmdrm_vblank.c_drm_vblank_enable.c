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
struct drm_vblank_crtc {int /*<<< orphan*/  enabled; int /*<<< orphan*/  refcount; } ;
struct drm_device {int /*<<< orphan*/  vblank_time_lock; int /*<<< orphan*/  vbl_lock; struct drm_vblank_crtc* vblank; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned int,int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int __enable_vblank (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_update_vblank_count (struct drm_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_vblank_enable(struct drm_device *dev, unsigned int pipe)
{
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];
	int ret = 0;

	assert_spin_locked(&dev->vbl_lock);

	spin_lock(&dev->vblank_time_lock);

	if (!vblank->enabled) {
		/*
		 * Enable vblank irqs under vblank_time_lock protection.
		 * All vblank count & timestamp updates are held off
		 * until we are done reinitializing master counter and
		 * timestamps. Filtercode in drm_handle_vblank() will
		 * prevent double-accounting of same vblank interval.
		 */
		ret = __enable_vblank(dev, pipe);
		DRM_DEBUG("enabling vblank on crtc %u, ret: %d\n", pipe, ret);
		if (ret) {
			atomic_dec(&vblank->refcount);
		} else {
			drm_update_vblank_count(dev, pipe, 0);
			/* drm_update_vblank_count() includes a wmb so we just
			 * need to ensure that the compiler emits the write
			 * to mark the vblank as enabled after the call
			 * to drm_update_vblank_count().
			 */
			WRITE_ONCE(vblank->enabled, true);
		}
	}

	spin_unlock(&dev->vblank_time_lock);

	return ret;
}