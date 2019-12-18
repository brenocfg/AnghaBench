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
struct drm_rect {int dummy; } ;
struct drm_atomic_helper_damage_iter {int full_update; size_t curr_clip; size_t num_clips; struct drm_rect plane_src; struct drm_rect* clips; } ;

/* Variables and functions */
 scalar_t__ drm_rect_intersect (struct drm_rect*,struct drm_rect*) ; 

bool
drm_atomic_helper_damage_iter_next(struct drm_atomic_helper_damage_iter *iter,
				   struct drm_rect *rect)
{
	bool ret = false;

	if (iter->full_update) {
		*rect = iter->plane_src;
		iter->full_update = false;
		return true;
	}

	while (iter->curr_clip < iter->num_clips) {
		*rect = iter->clips[iter->curr_clip];
		iter->curr_clip++;

		if (drm_rect_intersect(rect, &iter->plane_src)) {
			ret = true;
			break;
		}
	}

	return ret;
}