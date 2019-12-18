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
typedef  size_t u32 ;
struct vc4_plane_state {scalar_t__ dlist_count; scalar_t__ pos0_offset; scalar_t__ pos2_offset; scalar_t__ ptr0_offset; size_t lbm_offset; scalar_t__* dlist; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {struct drm_plane_state* state; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vc4_plane_state* to_vc4_plane_state (struct drm_plane_state*) ; 
 scalar_t__ vc4_lbm_size (struct drm_plane_state*) ; 
 int vc4_plane_mode_set (struct drm_plane*,struct drm_plane_state*) ; 

__attribute__((used)) static int vc4_plane_atomic_async_check(struct drm_plane *plane,
					struct drm_plane_state *state)
{
	struct vc4_plane_state *old_vc4_state, *new_vc4_state;
	int ret;
	u32 i;

	ret = vc4_plane_mode_set(plane, state);
	if (ret)
		return ret;

	old_vc4_state = to_vc4_plane_state(plane->state);
	new_vc4_state = to_vc4_plane_state(state);
	if (old_vc4_state->dlist_count != new_vc4_state->dlist_count ||
	    old_vc4_state->pos0_offset != new_vc4_state->pos0_offset ||
	    old_vc4_state->pos2_offset != new_vc4_state->pos2_offset ||
	    old_vc4_state->ptr0_offset != new_vc4_state->ptr0_offset ||
	    vc4_lbm_size(plane->state) != vc4_lbm_size(state))
		return -EINVAL;

	/* Only pos0, pos2 and ptr0 DWORDS can be updated in an async update
	 * if anything else has changed, fallback to a sync update.
	 */
	for (i = 0; i < new_vc4_state->dlist_count; i++) {
		if (i == new_vc4_state->pos0_offset ||
		    i == new_vc4_state->pos2_offset ||
		    i == new_vc4_state->ptr0_offset ||
		    (new_vc4_state->lbm_offset &&
		     i == new_vc4_state->lbm_offset))
			continue;

		if (new_vc4_state->dlist[i] != old_vc4_state->dlist[i])
			return -EINVAL;
	}

	return 0;
}