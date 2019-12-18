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
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_mode_set {struct drm_crtc* crtc; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct drm_atomic_state {struct drm_modeset_acquire_ctx* acquire_ctx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __drm_atomic_helper_set_config (struct drm_mode_set*,struct drm_atomic_state*) ; 
 int drm_atomic_commit (struct drm_atomic_state*) ; 
 struct drm_atomic_state* drm_atomic_state_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int handle_conflicting_encoders (struct drm_atomic_state*,int) ; 

int drm_atomic_helper_set_config(struct drm_mode_set *set,
				 struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_atomic_state *state;
	struct drm_crtc *crtc = set->crtc;
	int ret = 0;

	state = drm_atomic_state_alloc(crtc->dev);
	if (!state)
		return -ENOMEM;

	state->acquire_ctx = ctx;
	ret = __drm_atomic_helper_set_config(set, state);
	if (ret != 0)
		goto fail;

	ret = handle_conflicting_encoders(state, true);
	if (ret)
		return ret;

	ret = drm_atomic_commit(state);

fail:
	drm_atomic_state_put(state);
	return ret;
}