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
struct drm_display_mode {int flags; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_3D_MASK ; 

__attribute__((used)) static bool drm_mode_match_3d_flags(const struct drm_display_mode *mode1,
				    const struct drm_display_mode *mode2)
{
	return (mode1->flags & DRM_MODE_FLAG_3D_MASK) ==
		(mode2->flags & DRM_MODE_FLAG_3D_MASK);
}