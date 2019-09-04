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
struct intel_shared_dpll {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void hsw_ddi_lcpll_enable(struct drm_i915_private *dev_priv,
				 struct intel_shared_dpll *pll)
{
}