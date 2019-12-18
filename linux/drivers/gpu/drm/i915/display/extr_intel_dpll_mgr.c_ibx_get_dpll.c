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
struct intel_encoder {int dummy; } ;
struct intel_crtc_state {struct intel_shared_dpll* shared_dpll; int /*<<< orphan*/  dpll_hw_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_1__ base; int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_2__ base; scalar_t__ pipe; } ;
struct intel_atomic_state {int dummy; } ;
struct drm_i915_private {struct intel_shared_dpll* shared_dplls; } ;
typedef  enum intel_dpll_id { ____Placeholder_intel_dpll_id } intel_dpll_id ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL_ID_PCH_PLL_A ; 
 int /*<<< orphan*/  DPLL_ID_PCH_PLL_B ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 struct intel_shared_dpll* intel_find_shared_dpll (struct intel_atomic_state*,struct intel_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_reference_shared_dpll (struct intel_atomic_state*,struct intel_crtc*,struct intel_shared_dpll*,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ibx_get_dpll(struct intel_atomic_state *state,
			 struct intel_crtc *crtc,
			 struct intel_encoder *encoder)
{
	struct intel_crtc_state *crtc_state =
		intel_atomic_get_new_crtc_state(state, crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_shared_dpll *pll;
	enum intel_dpll_id i;

	if (HAS_PCH_IBX(dev_priv)) {
		/* Ironlake PCH has a fixed PLL->PCH pipe mapping. */
		i = (enum intel_dpll_id) crtc->pipe;
		pll = &dev_priv->shared_dplls[i];

		DRM_DEBUG_KMS("[CRTC:%d:%s] using pre-allocated %s\n",
			      crtc->base.base.id, crtc->base.name,
			      pll->info->name);
	} else {
		pll = intel_find_shared_dpll(state, crtc,
					     &crtc_state->dpll_hw_state,
					     DPLL_ID_PCH_PLL_A,
					     DPLL_ID_PCH_PLL_B);
	}

	if (!pll)
		return false;

	/* reference the pll */
	intel_reference_shared_dpll(state, crtc,
				    pll, &crtc_state->dpll_hw_state);

	crtc_state->shared_dpll = pll;

	return true;
}