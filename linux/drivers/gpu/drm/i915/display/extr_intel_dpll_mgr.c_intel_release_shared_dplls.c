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
struct intel_dpll_mgr {int /*<<< orphan*/  (* put_dplls ) (struct intel_atomic_state*,struct intel_crtc*) ;} ;
struct intel_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_atomic_state {TYPE_1__ base; } ;
struct drm_i915_private {struct intel_dpll_mgr* dpll_mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct intel_atomic_state*,struct intel_crtc*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_release_shared_dplls(struct intel_atomic_state *state,
				struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(state->base.dev);
	const struct intel_dpll_mgr *dpll_mgr = dev_priv->dpll_mgr;

	/*
	 * FIXME: this function is called for every platform having a
	 * compute_clock hook, even though the platform doesn't yet support
	 * the shared DPLL framework and intel_reserve_shared_dplls() is not
	 * called on those.
	 */
	if (!dpll_mgr)
		return;

	dpll_mgr->put_dplls(state, crtc);
}