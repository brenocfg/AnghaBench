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

/* Variables and functions */
 int GEN7_DOP_CLOCK_GATE_ENABLE ; 
 int /*<<< orphan*/  GEN7_MISCCPCTL ; 
 int /*<<< orphan*/  GEN8_L3SQCREG1 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int L3_GENERAL_PRIO_CREDITS (int) ; 
 int L3_HIGH_PRIO_CREDITS (int) ; 
 int L3_PRIO_CREDITS_MASK ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void gen8_set_l3sqc_credits(struct drm_i915_private *dev_priv,
				   int general_prio_credits,
				   int high_prio_credits)
{
	u32 misccpctl;
	u32 val;

	/* WaTempDisableDOPClkGating:bdw */
	misccpctl = I915_READ(GEN7_MISCCPCTL);
	I915_WRITE(GEN7_MISCCPCTL, misccpctl & ~GEN7_DOP_CLOCK_GATE_ENABLE);

	val = I915_READ(GEN8_L3SQCREG1);
	val &= ~L3_PRIO_CREDITS_MASK;
	val |= L3_GENERAL_PRIO_CREDITS(general_prio_credits);
	val |= L3_HIGH_PRIO_CREDITS(high_prio_credits);
	I915_WRITE(GEN8_L3SQCREG1, val);

	/*
	 * Wait at least 100 clocks before re-enabling clock gating.
	 * See the definition of L3SQCREG1 in BSpec.
	 */
	POSTING_READ(GEN8_L3SQCREG1);
	udelay(1);
	I915_WRITE(GEN7_MISCCPCTL, misccpctl);
}