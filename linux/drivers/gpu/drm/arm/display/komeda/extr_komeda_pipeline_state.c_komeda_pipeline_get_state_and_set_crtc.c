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
struct komeda_pipeline_state {struct drm_crtc* crtc; scalar_t__ active_comps; } ;
struct komeda_pipeline {int /*<<< orphan*/  id; } ;
struct komeda_crtc_state {int /*<<< orphan*/  affected_pipes; int /*<<< orphan*/  active_pipes; } ;
struct drm_crtc {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  EBUSY ; 
 struct komeda_pipeline_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct komeda_pipeline_state*) ; 
 int /*<<< orphan*/  drm_atomic_get_new_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_index (struct drm_crtc*) ; 
 scalar_t__ is_switching_user (struct drm_crtc*,struct drm_crtc*) ; 
 struct komeda_pipeline_state* komeda_pipeline_get_state (struct komeda_pipeline*,struct drm_atomic_state*) ; 
 struct komeda_crtc_state* to_kcrtc_st (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct komeda_pipeline_state *
komeda_pipeline_get_state_and_set_crtc(struct komeda_pipeline *pipe,
				       struct drm_atomic_state *state,
				       struct drm_crtc *crtc)
{
	struct komeda_pipeline_state *st;

	st = komeda_pipeline_get_state(pipe, state);
	if (IS_ERR(st))
		return st;

	if (is_switching_user(crtc, st->crtc)) {
		DRM_DEBUG_ATOMIC("CRTC%d required pipeline%d is busy.\n",
				 drm_crtc_index(crtc), pipe->id);
		return ERR_PTR(-EBUSY);
	}

	/* pipeline only can be disabled when the it is free or unused */
	if (!crtc && st->active_comps) {
		DRM_DEBUG_ATOMIC("Disabling a busy pipeline:%d.\n", pipe->id);
		return ERR_PTR(-EBUSY);
	}

	st->crtc = crtc;

	if (crtc) {
		struct komeda_crtc_state *kcrtc_st;

		kcrtc_st = to_kcrtc_st(drm_atomic_get_new_crtc_state(state,
								     crtc));

		kcrtc_st->active_pipes |= BIT(pipe->id);
		kcrtc_st->affected_pipes |= BIT(pipe->id);
	}
	return st;
}