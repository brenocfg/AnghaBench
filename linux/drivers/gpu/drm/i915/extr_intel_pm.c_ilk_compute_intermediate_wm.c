#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_wm_level {void* fbc_val; void* cur_val; void* spr_val; void* pri_val; int /*<<< orphan*/  enable; } ;
struct intel_pipe_wm {struct intel_wm_level* wm; int /*<<< orphan*/  sprites_scaled; int /*<<< orphan*/  sprites_enabled; int /*<<< orphan*/  pipe_enabled; } ;
struct TYPE_6__ {struct intel_pipe_wm optimal; struct intel_pipe_wm intermediate; } ;
struct TYPE_7__ {int need_postvbl_update; TYPE_2__ ilk; } ;
struct TYPE_8__ {int /*<<< orphan*/  active; int /*<<< orphan*/  state; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_3__ wm; TYPE_4__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct intel_atomic_state {scalar_t__ skip_intermediate_wm; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ drm_atomic_crtc_needs_modeset (TYPE_4__*) ; 
 int /*<<< orphan*/  ilk_validate_pipe_wm (struct drm_i915_private*,struct intel_pipe_wm*) ; 
 int ilk_wm_max_level (struct drm_i915_private*) ; 
 struct intel_crtc_state* intel_atomic_get_old_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 void* max (void*,void*) ; 
 scalar_t__ memcmp (struct intel_pipe_wm*,struct intel_pipe_wm*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_atomic_state* to_intel_atomic_state (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ilk_compute_intermediate_wm(struct intel_crtc_state *newstate)
{
	struct intel_crtc *intel_crtc = to_intel_crtc(newstate->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(intel_crtc->base.dev);
	struct intel_pipe_wm *a = &newstate->wm.ilk.intermediate;
	struct intel_atomic_state *intel_state =
		to_intel_atomic_state(newstate->base.state);
	const struct intel_crtc_state *oldstate =
		intel_atomic_get_old_crtc_state(intel_state, intel_crtc);
	const struct intel_pipe_wm *b = &oldstate->wm.ilk.optimal;
	int level, max_level = ilk_wm_max_level(dev_priv);

	/*
	 * Start with the final, target watermarks, then combine with the
	 * currently active watermarks to get values that are safe both before
	 * and after the vblank.
	 */
	*a = newstate->wm.ilk.optimal;
	if (!newstate->base.active || drm_atomic_crtc_needs_modeset(&newstate->base) ||
	    intel_state->skip_intermediate_wm)
		return 0;

	a->pipe_enabled |= b->pipe_enabled;
	a->sprites_enabled |= b->sprites_enabled;
	a->sprites_scaled |= b->sprites_scaled;

	for (level = 0; level <= max_level; level++) {
		struct intel_wm_level *a_wm = &a->wm[level];
		const struct intel_wm_level *b_wm = &b->wm[level];

		a_wm->enable &= b_wm->enable;
		a_wm->pri_val = max(a_wm->pri_val, b_wm->pri_val);
		a_wm->spr_val = max(a_wm->spr_val, b_wm->spr_val);
		a_wm->cur_val = max(a_wm->cur_val, b_wm->cur_val);
		a_wm->fbc_val = max(a_wm->fbc_val, b_wm->fbc_val);
	}

	/*
	 * We need to make sure that these merged watermark values are
	 * actually a valid configuration themselves.  If they're not,
	 * there's no safe way to transition from the old state to
	 * the new state, so we need to fail the atomic transaction.
	 */
	if (!ilk_validate_pipe_wm(dev_priv, a))
		return -EINVAL;

	/*
	 * If our intermediate WM are identical to the final WM, then we can
	 * omit the post-vblank programming; only update if it's different.
	 */
	if (memcmp(a, &newstate->wm.ilk.optimal, sizeof(*a)) != 0)
		newstate->wm.need_postvbl_update = true;

	return 0;
}