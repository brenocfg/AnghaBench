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

/* Variables and functions */
 int DRM_MODE_MATCH_FLAGS ; 
 int DRM_MODE_MATCH_TIMINGS ; 
 int drm_mode_match (struct drm_display_mode const*,struct drm_display_mode const*,int) ; 

bool drm_mode_equal_no_clocks_no_stereo(const struct drm_display_mode *mode1,
					const struct drm_display_mode *mode2)
{
	return drm_mode_match(mode1, mode2,
			      DRM_MODE_MATCH_TIMINGS |
			      DRM_MODE_MATCH_FLAGS);
}