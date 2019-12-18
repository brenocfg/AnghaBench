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
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  FDI_RX_CTL (int) ; 
 int FDI_RX_PLL_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_STATE_WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onoff (int) ; 

void assert_fdi_rx_pll(struct drm_i915_private *dev_priv,
		       enum pipe pipe, bool state)
{
	u32 val;
	bool cur_state;

	val = I915_READ(FDI_RX_CTL(pipe));
	cur_state = !!(val & FDI_RX_PLL_ENABLE);
	I915_STATE_WARN(cur_state != state,
	     "FDI RX PLL assertion failure (expected %s, current %s)\n",
			onoff(state), onoff(cur_state));
}