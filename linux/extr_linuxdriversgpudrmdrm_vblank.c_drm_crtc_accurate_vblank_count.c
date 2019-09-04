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
typedef  int /*<<< orphan*/  u64 ;
struct drm_device {int /*<<< orphan*/  vblank_time_lock; TYPE_1__* driver; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  get_vblank_timestamp; } ;

/* Variables and functions */
 int DRM_UT_VBL ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 unsigned int drm_crtc_index (struct drm_crtc*) ; 
 int drm_debug ; 
 int /*<<< orphan*/  drm_update_vblank_count (struct drm_device*,unsigned int,int) ; 
 int /*<<< orphan*/  drm_vblank_count (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u64 drm_crtc_accurate_vblank_count(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	unsigned int pipe = drm_crtc_index(crtc);
	u64 vblank;
	unsigned long flags;

	WARN_ONCE(drm_debug & DRM_UT_VBL && !dev->driver->get_vblank_timestamp,
		  "This function requires support for accurate vblank timestamps.");

	spin_lock_irqsave(&dev->vblank_time_lock, flags);

	drm_update_vblank_count(dev, pipe, false);
	vblank = drm_vblank_count(dev, pipe);

	spin_unlock_irqrestore(&dev->vblank_time_lock, flags);

	return vblank;
}