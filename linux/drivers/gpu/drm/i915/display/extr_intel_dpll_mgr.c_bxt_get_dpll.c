#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_shared_dpll {TYPE_3__* info; } ;
struct intel_encoder {scalar_t__ port; } ;
struct intel_crtc_state {struct intel_shared_dpll* shared_dpll; int /*<<< orphan*/  dpll_hw_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_1__ base; int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_2__ base; } ;
struct intel_atomic_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 int /*<<< orphan*/  bxt_ddi_dp_set_dpll_hw_state (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  bxt_ddi_hdmi_set_dpll_hw_state (struct intel_crtc_state*) ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 scalar_t__ intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 struct intel_shared_dpll* intel_get_shared_dpll_by_id (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_reference_shared_dpll (struct intel_atomic_state*,struct intel_crtc*,struct intel_shared_dpll*,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bxt_get_dpll(struct intel_atomic_state *state,
			 struct intel_crtc *crtc,
			 struct intel_encoder *encoder)
{
	struct intel_crtc_state *crtc_state =
		intel_atomic_get_new_crtc_state(state, crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_shared_dpll *pll;
	enum intel_dpll_id id;

	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI) &&
	    !bxt_ddi_hdmi_set_dpll_hw_state(crtc_state))
		return false;

	if (intel_crtc_has_dp_encoder(crtc_state) &&
	    !bxt_ddi_dp_set_dpll_hw_state(crtc_state))
		return false;

	/* 1:1 mapping between ports and PLLs */
	id = (enum intel_dpll_id) encoder->port;
	pll = intel_get_shared_dpll_by_id(dev_priv, id);

	DRM_DEBUG_KMS("[CRTC:%d:%s] using pre-allocated %s\n",
		      crtc->base.base.id, crtc->base.name, pll->info->name);

	intel_reference_shared_dpll(state, crtc,
				    pll, &crtc_state->dpll_hw_state);

	crtc_state->shared_dpll = pll;

	return true;
}