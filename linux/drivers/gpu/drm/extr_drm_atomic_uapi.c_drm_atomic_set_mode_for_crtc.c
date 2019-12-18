#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode ;
struct drm_mode_modeinfo {int dummy; } ;
struct drm_display_mode {int /*<<< orphan*/  name; } ;
struct drm_crtc_state {int enable; int /*<<< orphan*/  mode; int /*<<< orphan*/ * mode_blob; struct drm_crtc* crtc; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {int /*<<< orphan*/  name; TYPE_1__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_crtc_state*,...) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_convert_to_umode (struct drm_mode_modeinfo*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_mode_copy (int /*<<< orphan*/ *,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_property_blob_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * drm_property_create_blob (int /*<<< orphan*/ ,int,struct drm_mode_modeinfo*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct drm_display_mode const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int drm_atomic_set_mode_for_crtc(struct drm_crtc_state *state,
				 const struct drm_display_mode *mode)
{
	struct drm_crtc *crtc = state->crtc;
	struct drm_mode_modeinfo umode;

	/* Early return for no change. */
	if (mode && memcmp(&state->mode, mode, sizeof(*mode)) == 0)
		return 0;

	drm_property_blob_put(state->mode_blob);
	state->mode_blob = NULL;

	if (mode) {
		drm_mode_convert_to_umode(&umode, mode);
		state->mode_blob =
			drm_property_create_blob(state->crtc->dev,
		                                 sizeof(umode),
		                                 &umode);
		if (IS_ERR(state->mode_blob))
			return PTR_ERR(state->mode_blob);

		drm_mode_copy(&state->mode, mode);
		state->enable = true;
		DRM_DEBUG_ATOMIC("Set [MODE:%s] for [CRTC:%d:%s] state %p\n",
				 mode->name, crtc->base.id, crtc->name, state);
	} else {
		memset(&state->mode, 0, sizeof(state->mode));
		state->enable = false;
		DRM_DEBUG_ATOMIC("Set [NOMODE] for [CRTC:%d:%s] state %p\n",
				 crtc->base.id, crtc->name, state);
	}

	return 0;
}