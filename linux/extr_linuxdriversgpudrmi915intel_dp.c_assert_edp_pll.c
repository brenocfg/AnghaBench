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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_A ; 
 int DP_PLL_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_STATE_WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onoff (int) ; 

__attribute__((used)) static void assert_edp_pll(struct drm_i915_private *dev_priv, bool state)
{
	bool cur_state = I915_READ(DP_A) & DP_PLL_ENABLE;

	I915_STATE_WARN(cur_state != state,
			"eDP PLL state assertion failure (expected %s, current %s)\n",
			onoff(state), onoff(cur_state));
}