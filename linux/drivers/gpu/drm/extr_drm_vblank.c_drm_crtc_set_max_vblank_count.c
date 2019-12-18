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
typedef  int /*<<< orphan*/  u32 ;
struct drm_vblank_crtc {int /*<<< orphan*/  max_vblank_count; int /*<<< orphan*/  inmodeset; } ;
struct drm_device {int max_vblank_count; struct drm_vblank_crtc* vblank; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int drm_crtc_index (struct drm_crtc*) ; 

void drm_crtc_set_max_vblank_count(struct drm_crtc *crtc,
				   u32 max_vblank_count)
{
	struct drm_device *dev = crtc->dev;
	unsigned int pipe = drm_crtc_index(crtc);
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];

	WARN_ON(dev->max_vblank_count);
	WARN_ON(!READ_ONCE(vblank->inmodeset));

	vblank->max_vblank_count = max_vblank_count;
}