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
 int DSTATE_DOT_CLOCK_GATING ; 
 int DSTATE_GFX_CLOCK_GATING ; 
 int DSTATE_PLL_D3_OFF ; 
 int /*<<< orphan*/  D_STATE ; 
 int /*<<< orphan*/  ECOSKPD ; 
 int /*<<< orphan*/  ECO_FLIP_DONE ; 
 int /*<<< orphan*/  ECO_GATING_CX_ONLY ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INSTPM ; 
 int /*<<< orphan*/  INSTPM_AGPBUSY_INT_EN ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MI_ARB_C3_LP_WRITE_ENABLE ; 
 int /*<<< orphan*/  MI_ARB_DISPLAY_TRICKLE_FEED_DISABLE ; 
 int /*<<< orphan*/  MI_ARB_STATE ; 
 int _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen3_init_clock_gating(struct drm_i915_private *dev_priv)
{
	u32 dstate = I915_READ(D_STATE);

	dstate |= DSTATE_PLL_D3_OFF | DSTATE_GFX_CLOCK_GATING |
		DSTATE_DOT_CLOCK_GATING;
	I915_WRITE(D_STATE, dstate);

	if (IS_PINEVIEW(dev_priv))
		I915_WRITE(ECOSKPD, _MASKED_BIT_ENABLE(ECO_GATING_CX_ONLY));

	/* IIR "flip pending" means done if this bit is set */
	I915_WRITE(ECOSKPD, _MASKED_BIT_DISABLE(ECO_FLIP_DONE));

	/* interrupts should cause a wake up from C3 */
	I915_WRITE(INSTPM, _MASKED_BIT_ENABLE(INSTPM_AGPBUSY_INT_EN));

	/* On GEN3 we really need to make sure the ARB C3 LP bit is set */
	I915_WRITE(MI_ARB_STATE, _MASKED_BIT_ENABLE(MI_ARB_C3_LP_WRITE_ENABLE));

	I915_WRITE(MI_ARB_STATE,
		   _MASKED_BIT_ENABLE(MI_ARB_DISPLAY_TRICKLE_FEED_DISABLE));
}