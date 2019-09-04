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
 unsigned int DRM_MODE_MATCH_3D_FLAGS ; 
 unsigned int DRM_MODE_MATCH_ASPECT_RATIO ; 
 unsigned int DRM_MODE_MATCH_CLOCK ; 
 unsigned int DRM_MODE_MATCH_FLAGS ; 
 unsigned int DRM_MODE_MATCH_TIMINGS ; 
 int /*<<< orphan*/  drm_mode_match_3d_flags (struct drm_display_mode const*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_mode_match_aspect_ratio (struct drm_display_mode const*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_mode_match_clock (struct drm_display_mode const*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_mode_match_flags (struct drm_display_mode const*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_mode_match_timings (struct drm_display_mode const*,struct drm_display_mode const*) ; 

bool drm_mode_match(const struct drm_display_mode *mode1,
		    const struct drm_display_mode *mode2,
		    unsigned int match_flags)
{
	if (!mode1 && !mode2)
		return true;

	if (!mode1 || !mode2)
		return false;

	if (match_flags & DRM_MODE_MATCH_TIMINGS &&
	    !drm_mode_match_timings(mode1, mode2))
		return false;

	if (match_flags & DRM_MODE_MATCH_CLOCK &&
	    !drm_mode_match_clock(mode1, mode2))
		return false;

	if (match_flags & DRM_MODE_MATCH_FLAGS &&
	    !drm_mode_match_flags(mode1, mode2))
		return false;

	if (match_flags & DRM_MODE_MATCH_3D_FLAGS &&
	    !drm_mode_match_3d_flags(mode1, mode2))
		return false;

	if (match_flags & DRM_MODE_MATCH_ASPECT_RATIO &&
	    !drm_mode_match_aspect_ratio(mode1, mode2))
		return false;

	return true;
}