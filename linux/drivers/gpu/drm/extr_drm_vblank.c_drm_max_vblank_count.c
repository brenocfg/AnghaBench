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
struct drm_vblank_crtc {scalar_t__ max_vblank_count; } ;
struct drm_device {int /*<<< orphan*/  max_vblank_count; struct drm_vblank_crtc* vblank; } ;

/* Variables and functions */

__attribute__((used)) static u32 drm_max_vblank_count(struct drm_device *dev, unsigned int pipe)
{
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];

	return vblank->max_vblank_count ?: dev->max_vblank_count;
}