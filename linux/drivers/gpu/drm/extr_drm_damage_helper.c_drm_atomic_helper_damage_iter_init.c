#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x1; int y1; int x2; int y2; } ;
struct drm_plane_state {TYPE_2__ src; int /*<<< orphan*/  visible; int /*<<< orphan*/  fb; int /*<<< orphan*/  crtc; } ;
struct TYPE_4__ {int x1; int y1; int x2; int y2; } ;
struct drm_atomic_helper_damage_iter {int full_update; scalar_t__ num_clips; int /*<<< orphan*/ * clips; TYPE_1__ plane_src; } ;

/* Variables and functions */
 int /*<<< orphan*/ * drm_helper_get_plane_damage_clips (struct drm_plane_state const*) ; 
 scalar_t__ drm_plane_get_damage_clips_count (struct drm_plane_state const*) ; 
 int /*<<< orphan*/  drm_rect_equals (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (struct drm_atomic_helper_damage_iter*,int /*<<< orphan*/ ,int) ; 

void
drm_atomic_helper_damage_iter_init(struct drm_atomic_helper_damage_iter *iter,
				   const struct drm_plane_state *old_state,
				   const struct drm_plane_state *state)
{
	memset(iter, 0, sizeof(*iter));

	if (!state || !state->crtc || !state->fb || !state->visible)
		return;

	iter->clips = drm_helper_get_plane_damage_clips(state);
	iter->num_clips = drm_plane_get_damage_clips_count(state);

	/* Round down for x1/y1 and round up for x2/y2 to catch all pixels */
	iter->plane_src.x1 = state->src.x1 >> 16;
	iter->plane_src.y1 = state->src.y1 >> 16;
	iter->plane_src.x2 = (state->src.x2 >> 16) + !!(state->src.x2 & 0xFFFF);
	iter->plane_src.y2 = (state->src.y2 >> 16) + !!(state->src.y2 & 0xFFFF);

	if (!iter->clips || !drm_rect_equals(&state->src, &old_state->src)) {
		iter->clips = NULL;
		iter->num_clips = 0;
		iter->full_update = true;
	}
}