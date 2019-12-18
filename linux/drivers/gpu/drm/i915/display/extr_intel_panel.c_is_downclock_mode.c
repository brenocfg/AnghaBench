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
struct drm_display_mode {scalar_t__ clock; } ;

/* Variables and functions */
 int DRM_MODE_MATCH_3D_FLAGS ; 
 int DRM_MODE_MATCH_FLAGS ; 
 int DRM_MODE_MATCH_TIMINGS ; 
 scalar_t__ drm_mode_match (struct drm_display_mode const*,struct drm_display_mode const*,int) ; 

__attribute__((used)) static bool is_downclock_mode(const struct drm_display_mode *downclock_mode,
			      const struct drm_display_mode *fixed_mode)
{
	return drm_mode_match(downclock_mode, fixed_mode,
			      DRM_MODE_MATCH_TIMINGS |
			      DRM_MODE_MATCH_FLAGS |
			      DRM_MODE_MATCH_3D_FLAGS) &&
		downclock_mode->clock < fixed_mode->clock;
}