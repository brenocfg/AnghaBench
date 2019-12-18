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
struct intel_dpll_hw_state {int /*<<< orphan*/  fp1; int /*<<< orphan*/  fp0; int /*<<< orphan*/  dpll_md; int /*<<< orphan*/  dpll; } ;
struct drm_i915_private {TYPE_1__* dpll_mgr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dump_hw_state ) (struct drm_i915_private*,struct intel_dpll_hw_state const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*,struct intel_dpll_hw_state const*) ; 

void intel_dpll_dump_hw_state(struct drm_i915_private *dev_priv,
			      const struct intel_dpll_hw_state *hw_state)
{
	if (dev_priv->dpll_mgr) {
		dev_priv->dpll_mgr->dump_hw_state(dev_priv, hw_state);
	} else {
		/* fallback for platforms that don't use the shared dpll
		 * infrastructure
		 */
		DRM_DEBUG_KMS("dpll_hw_state: dpll: 0x%x, dpll_md: 0x%x, "
			      "fp0: 0x%x, fp1: 0x%x\n",
			      hw_state->dpll,
			      hw_state->dpll_md,
			      hw_state->fp0,
			      hw_state->fp1);
	}
}