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
struct drm_vblank_crtc {int inmodeset; int /*<<< orphan*/  refcount; } ;
struct drm_device {int /*<<< orphan*/  vblank_event_list; int /*<<< orphan*/  vbl_lock; struct drm_vblank_crtc* vblank; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned int drm_crtc_index (struct drm_crtc*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void drm_crtc_vblank_reset(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	unsigned long irqflags;
	unsigned int pipe = drm_crtc_index(crtc);
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];

	spin_lock_irqsave(&dev->vbl_lock, irqflags);
	/*
	 * Prevent subsequent drm_vblank_get() from enabling the vblank
	 * interrupt by bumping the refcount.
	 */
	if (!vblank->inmodeset) {
		atomic_inc(&vblank->refcount);
		vblank->inmodeset = 1;
	}
	spin_unlock_irqrestore(&dev->vbl_lock, irqflags);

	WARN_ON(!list_empty(&dev->vblank_event_list));
}