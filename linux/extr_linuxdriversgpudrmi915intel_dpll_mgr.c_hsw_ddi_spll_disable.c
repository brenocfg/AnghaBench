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
typedef  int uint32_t ;
struct intel_shared_dpll {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLL_CTL ; 
 int SPLL_PLL_ENABLE ; 

__attribute__((used)) static void hsw_ddi_spll_disable(struct drm_i915_private *dev_priv,
				 struct intel_shared_dpll *pll)
{
	uint32_t val;

	val = I915_READ(SPLL_CTL);
	I915_WRITE(SPLL_CTL, val & ~SPLL_PLL_ENABLE);
	POSTING_READ(SPLL_CTL);
}