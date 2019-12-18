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
struct drm_vblank_crtc {int /*<<< orphan*/  refcount; scalar_t__ inmodeset; int /*<<< orphan*/  enabled; } ;
struct drm_device {unsigned int num_crtcs; int /*<<< orphan*/  vbl_lock; struct drm_vblank_crtc* vblank; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_VBL (char*,unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 unsigned int drm_crtc_index (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_reset_vblank_timestamp (struct drm_device*,unsigned int) ; 
 int drm_vblank_enable (struct drm_device*,unsigned int) ; 
 scalar_t__ drm_vblank_offdelay ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void drm_crtc_vblank_on(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	unsigned int pipe = drm_crtc_index(crtc);
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];
	unsigned long irqflags;

	if (WARN_ON(pipe >= dev->num_crtcs))
		return;

	spin_lock_irqsave(&dev->vbl_lock, irqflags);
	DRM_DEBUG_VBL("crtc %d, vblank enabled %d, inmodeset %d\n",
		      pipe, vblank->enabled, vblank->inmodeset);

	/* Drop our private "prevent drm_vblank_get" refcount */
	if (vblank->inmodeset) {
		atomic_dec(&vblank->refcount);
		vblank->inmodeset = 0;
	}

	drm_reset_vblank_timestamp(dev, pipe);

	/*
	 * re-enable interrupts if there are users left, or the
	 * user wishes vblank interrupts to be enabled all the time.
	 */
	if (atomic_read(&vblank->refcount) != 0 || drm_vblank_offdelay == 0)
		WARN_ON(drm_vblank_enable(dev, pipe));
	spin_unlock_irqrestore(&dev->vbl_lock, irqflags);
}