#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_plane_state {struct drm_crtc* crtc; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct drm_plane {scalar_t__ type; TYPE_1__ base; int /*<<< orphan*/  state; } ;
struct drm_crtc_state {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_3__* dev; TYPE_2__ base; } ;
struct drm_atomic_state {int dummy; } ;
struct dm_plane_state {struct dc_plane_state* dc_state; } ;
struct dm_crtc_state {int /*<<< orphan*/  stream; } ;
struct dm_atomic_state {int /*<<< orphan*/  context; } ;
struct TYPE_9__ {int full_update; } ;
struct TYPE_10__ {TYPE_4__ bits; } ;
struct dc_plane_state {TYPE_5__ update_flags; } ;
struct dc {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DRM_PLANE_TYPE_CURSOR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WARN_ON (struct dc_plane_state*) ; 
 int /*<<< orphan*/  dc_add_plane_to_context (struct dc*,int /*<<< orphan*/ ,struct dc_plane_state*,int /*<<< orphan*/ ) ; 
 struct dc_plane_state* dc_create_plane_state (struct dc*) ; 
 int /*<<< orphan*/  dc_plane_state_release (struct dc_plane_state*) ; 
 int /*<<< orphan*/  dc_remove_plane_from_context (struct dc*,int /*<<< orphan*/ ,struct dc_plane_state*,int /*<<< orphan*/ ) ; 
 int dm_atomic_get_state (struct drm_atomic_state*,struct dm_atomic_state**) ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 struct drm_crtc_state* drm_atomic_get_old_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 scalar_t__ drm_atomic_plane_disabling (int /*<<< orphan*/ ,struct drm_plane_state*) ; 
 int fill_dc_plane_attributes (int /*<<< orphan*/ ,struct dc_plane_state*,struct drm_plane_state*,struct drm_crtc_state*) ; 
 int should_reset_plane (struct drm_atomic_state*,struct drm_plane*,struct drm_plane_state*,struct drm_plane_state*) ; 
 struct dm_crtc_state* to_dm_crtc_state (struct drm_crtc_state*) ; 
 struct dm_plane_state* to_dm_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static int dm_update_plane_state(struct dc *dc,
				 struct drm_atomic_state *state,
				 struct drm_plane *plane,
				 struct drm_plane_state *old_plane_state,
				 struct drm_plane_state *new_plane_state,
				 bool enable,
				 bool *lock_and_validation_needed)
{

	struct dm_atomic_state *dm_state = NULL;
	struct drm_crtc *new_plane_crtc, *old_plane_crtc;
	struct drm_crtc_state *old_crtc_state, *new_crtc_state;
	struct dm_crtc_state *dm_new_crtc_state, *dm_old_crtc_state;
	struct dm_plane_state *dm_new_plane_state, *dm_old_plane_state;
	bool needs_reset;
	int ret = 0;


	new_plane_crtc = new_plane_state->crtc;
	old_plane_crtc = old_plane_state->crtc;
	dm_new_plane_state = to_dm_plane_state(new_plane_state);
	dm_old_plane_state = to_dm_plane_state(old_plane_state);

	/*TODO Implement atomic check for cursor plane */
	if (plane->type == DRM_PLANE_TYPE_CURSOR)
		return 0;

	needs_reset = should_reset_plane(state, plane, old_plane_state,
					 new_plane_state);

	/* Remove any changed/removed planes */
	if (!enable) {
		if (!needs_reset)
			return 0;

		if (!old_plane_crtc)
			return 0;

		old_crtc_state = drm_atomic_get_old_crtc_state(
				state, old_plane_crtc);
		dm_old_crtc_state = to_dm_crtc_state(old_crtc_state);

		if (!dm_old_crtc_state->stream)
			return 0;

		DRM_DEBUG_ATOMIC("Disabling DRM plane: %d on DRM crtc %d\n",
				plane->base.id, old_plane_crtc->base.id);

		ret = dm_atomic_get_state(state, &dm_state);
		if (ret)
			return ret;

		if (!dc_remove_plane_from_context(
				dc,
				dm_old_crtc_state->stream,
				dm_old_plane_state->dc_state,
				dm_state->context)) {

			ret = EINVAL;
			return ret;
		}


		dc_plane_state_release(dm_old_plane_state->dc_state);
		dm_new_plane_state->dc_state = NULL;

		*lock_and_validation_needed = true;

	} else { /* Add new planes */
		struct dc_plane_state *dc_new_plane_state;

		if (drm_atomic_plane_disabling(plane->state, new_plane_state))
			return 0;

		if (!new_plane_crtc)
			return 0;

		new_crtc_state = drm_atomic_get_new_crtc_state(state, new_plane_crtc);
		dm_new_crtc_state = to_dm_crtc_state(new_crtc_state);

		if (!dm_new_crtc_state->stream)
			return 0;

		if (!needs_reset)
			return 0;

		WARN_ON(dm_new_plane_state->dc_state);

		dc_new_plane_state = dc_create_plane_state(dc);
		if (!dc_new_plane_state)
			return -ENOMEM;

		DRM_DEBUG_DRIVER("Enabling DRM plane: %d on DRM crtc %d\n",
				plane->base.id, new_plane_crtc->base.id);

		ret = fill_dc_plane_attributes(
			new_plane_crtc->dev->dev_private,
			dc_new_plane_state,
			new_plane_state,
			new_crtc_state);
		if (ret) {
			dc_plane_state_release(dc_new_plane_state);
			return ret;
		}

		ret = dm_atomic_get_state(state, &dm_state);
		if (ret) {
			dc_plane_state_release(dc_new_plane_state);
			return ret;
		}

		/*
		 * Any atomic check errors that occur after this will
		 * not need a release. The plane state will be attached
		 * to the stream, and therefore part of the atomic
		 * state. It'll be released when the atomic state is
		 * cleaned.
		 */
		if (!dc_add_plane_to_context(
				dc,
				dm_new_crtc_state->stream,
				dc_new_plane_state,
				dm_state->context)) {

			dc_plane_state_release(dc_new_plane_state);
			return -EINVAL;
		}

		dm_new_plane_state->dc_state = dc_new_plane_state;

		/* Tell DC to do a full surface update every time there
		 * is a plane change. Inefficient, but works for now.
		 */
		dm_new_plane_state->dc_state->update_flags.bits.full_update = 1;

		*lock_and_validation_needed = true;
	}


	return ret;
}