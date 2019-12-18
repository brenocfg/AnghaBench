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
 scalar_t__ HAS_PCH_LPT_LP (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int PCH_LP_PARTITION_LEVEL_DISABLE ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  SOUTH_DSPCLK_GATE_D ; 
 int /*<<< orphan*/  TRANS_CHICKEN1 (int /*<<< orphan*/ ) ; 
 int TRANS_CHICKEN1_DP0UNIT_GC_DISABLE ; 

__attribute__((used)) static void lpt_init_clock_gating(struct drm_i915_private *dev_priv)
{
	/*
	 * TODO: this bit should only be enabled when really needed, then
	 * disabled when not needed anymore in order to save power.
	 */
	if (HAS_PCH_LPT_LP(dev_priv))
		I915_WRITE(SOUTH_DSPCLK_GATE_D,
			   I915_READ(SOUTH_DSPCLK_GATE_D) |
			   PCH_LP_PARTITION_LEVEL_DISABLE);

	/* WADPOClockGatingDisable:hsw */
	I915_WRITE(TRANS_CHICKEN1(PIPE_A),
		   I915_READ(TRANS_CHICKEN1(PIPE_A)) |
		   TRANS_CHICKEN1_DP0UNIT_GC_DISABLE);
}