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
struct intel_dpll_hw_state {int /*<<< orphan*/  pcsdw12; int /*<<< orphan*/  pll10; int /*<<< orphan*/  pll9; int /*<<< orphan*/  pll8; int /*<<< orphan*/  pll6; int /*<<< orphan*/  pll3; int /*<<< orphan*/  pll2; int /*<<< orphan*/  pll1; int /*<<< orphan*/  pll0; int /*<<< orphan*/  ebb4; int /*<<< orphan*/  ebb0; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bxt_dump_hw_state(struct drm_i915_private *dev_priv,
			      const struct intel_dpll_hw_state *hw_state)
{
	DRM_DEBUG_KMS("dpll_hw_state: ebb0: 0x%x, ebb4: 0x%x,"
		      "pll0: 0x%x, pll1: 0x%x, pll2: 0x%x, pll3: 0x%x, "
		      "pll6: 0x%x, pll8: 0x%x, pll9: 0x%x, pll10: 0x%x, pcsdw12: 0x%x\n",
		      hw_state->ebb0,
		      hw_state->ebb4,
		      hw_state->pll0,
		      hw_state->pll1,
		      hw_state->pll2,
		      hw_state->pll3,
		      hw_state->pll6,
		      hw_state->pll8,
		      hw_state->pll9,
		      hw_state->pll10,
		      hw_state->pcsdw12);
}