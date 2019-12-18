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
struct intel_dpll_hw_state {int /*<<< orphan*/  cfgcr1; int /*<<< orphan*/  cfgcr0; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnl_dump_hw_state(struct drm_i915_private *dev_priv,
			      const struct intel_dpll_hw_state *hw_state)
{
	DRM_DEBUG_KMS("dpll_hw_state: "
		      "cfgcr0: 0x%x, cfgcr1: 0x%x\n",
		      hw_state->cfgcr0,
		      hw_state->cfgcr1);
}