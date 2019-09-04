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
typedef  scalar_t__ uint32_t ;
struct drm_rect {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_IMG_HEIGHT ; 
 scalar_t__ MAX_IMG_WIDTH ; 
 scalar_t__ drm_rect_equals (struct drm_rect*,struct drm_rect*) ; 
 scalar_t__ drm_rect_height (struct drm_rect*) ; 
 scalar_t__ drm_rect_intersect (struct drm_rect*,struct drm_rect*) ; 
 scalar_t__ drm_rect_width (struct drm_rect*) ; 

__attribute__((used)) static bool dpu_plane_validate_src(struct drm_rect *src,
				   struct drm_rect *fb_rect,
				   uint32_t min_src_size)
{
	/* Ensure fb size is supported */
	if (drm_rect_width(fb_rect) > MAX_IMG_WIDTH ||
	    drm_rect_height(fb_rect) > MAX_IMG_HEIGHT)
		return false;

	/* Ensure src rect is above the minimum size */
	if (drm_rect_width(src) < min_src_size ||
	    drm_rect_height(src) < min_src_size)
		return false;

	/* Ensure src is fully encapsulated in fb */
	return drm_rect_intersect(fb_rect, src) &&
		drm_rect_equals(fb_rect, src);
}