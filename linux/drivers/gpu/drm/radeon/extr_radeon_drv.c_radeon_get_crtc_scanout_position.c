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
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int radeon_get_crtc_scanoutpos (struct drm_device*,unsigned int,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct drm_display_mode const*) ; 

__attribute__((used)) static bool
radeon_get_crtc_scanout_position(struct drm_device *dev, unsigned int pipe,
				 bool in_vblank_irq, int *vpos, int *hpos,
				 ktime_t *stime, ktime_t *etime,
				 const struct drm_display_mode *mode)
{
	return radeon_get_crtc_scanoutpos(dev, pipe, 0, vpos, hpos,
					  stime, etime, mode);
}