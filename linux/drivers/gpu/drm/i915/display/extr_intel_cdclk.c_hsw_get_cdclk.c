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
typedef  int u32 ;
struct intel_cdclk_state {int cdclk; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_STRAP ; 
 int HSW_CDCLK_LIMIT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HSW_ULT (struct drm_i915_private*) ; 
 int LCPLL_CD_SOURCE_FCLK ; 
 int LCPLL_CLK_FREQ_450 ; 
 int LCPLL_CLK_FREQ_MASK ; 
 int /*<<< orphan*/  LCPLL_CTL ; 

__attribute__((used)) static void hsw_get_cdclk(struct drm_i915_private *dev_priv,
			  struct intel_cdclk_state *cdclk_state)
{
	u32 lcpll = I915_READ(LCPLL_CTL);
	u32 freq = lcpll & LCPLL_CLK_FREQ_MASK;

	if (lcpll & LCPLL_CD_SOURCE_FCLK)
		cdclk_state->cdclk = 800000;
	else if (I915_READ(FUSE_STRAP) & HSW_CDCLK_LIMIT)
		cdclk_state->cdclk = 450000;
	else if (freq == LCPLL_CLK_FREQ_450)
		cdclk_state->cdclk = 450000;
	else if (IS_HSW_ULT(dev_priv))
		cdclk_state->cdclk = 337500;
	else
		cdclk_state->cdclk = 540000;
}