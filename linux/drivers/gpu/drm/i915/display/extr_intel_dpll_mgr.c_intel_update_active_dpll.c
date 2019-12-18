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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_dpll_mgr {int /*<<< orphan*/  (* update_active_dpll ) (struct intel_atomic_state*,struct intel_crtc*,struct intel_encoder*) ;} ;
struct intel_crtc {int dummy; } ;
struct intel_atomic_state {int dummy; } ;
struct drm_i915_private {struct intel_dpll_mgr* dpll_mgr; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct intel_atomic_state*,struct intel_crtc*,struct intel_encoder*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_update_active_dpll(struct intel_atomic_state *state,
			      struct intel_crtc *crtc,
			      struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	const struct intel_dpll_mgr *dpll_mgr = dev_priv->dpll_mgr;

	if (WARN_ON(!dpll_mgr))
		return;

	dpll_mgr->update_active_dpll(state, crtc, encoder);
}