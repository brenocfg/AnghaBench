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
struct intel_shared_dpll {int dummy; } ;
struct intel_encoder {int dummy; } ;
struct intel_dpll_mgr {struct intel_shared_dpll* (* get_dpll ) (struct intel_crtc*,struct intel_crtc_state*,struct intel_encoder*) ;} ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_1__ base; } ;
struct drm_i915_private {struct intel_dpll_mgr* dpll_mgr; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct intel_shared_dpll* stub1 (struct intel_crtc*,struct intel_crtc_state*,struct intel_encoder*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

struct intel_shared_dpll *
intel_get_shared_dpll(struct intel_crtc *crtc,
		      struct intel_crtc_state *crtc_state,
		      struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	const struct intel_dpll_mgr *dpll_mgr = dev_priv->dpll_mgr;

	if (WARN_ON(!dpll_mgr))
		return NULL;

	return dpll_mgr->get_dpll(crtc, crtc_state, encoder);
}