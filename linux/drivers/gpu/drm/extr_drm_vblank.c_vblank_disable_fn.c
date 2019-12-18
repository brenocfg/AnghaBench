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
struct timer_list {int dummy; } ;
struct drm_vblank_crtc {unsigned int pipe; scalar_t__ enabled; int /*<<< orphan*/  refcount; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  vbl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_timer ; 
 int /*<<< orphan*/  drm_vblank_disable_and_save (struct drm_device*,unsigned int) ; 
 struct drm_vblank_crtc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_vblank_crtc* vblank ; 

__attribute__((used)) static void vblank_disable_fn(struct timer_list *t)
{
	struct drm_vblank_crtc *vblank = from_timer(vblank, t, disable_timer);
	struct drm_device *dev = vblank->dev;
	unsigned int pipe = vblank->pipe;
	unsigned long irqflags;

	spin_lock_irqsave(&dev->vbl_lock, irqflags);
	if (atomic_read(&vblank->refcount) == 0 && vblank->enabled) {
		DRM_DEBUG("disabling vblank on crtc %u\n", pipe);
		drm_vblank_disable_and_save(dev, pipe);
	}
	spin_unlock_irqrestore(&dev->vbl_lock, irqflags);
}