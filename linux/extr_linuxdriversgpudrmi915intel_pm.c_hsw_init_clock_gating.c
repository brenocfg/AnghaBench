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
 int /*<<< orphan*/  CACHE_MODE_0_GEN7 ; 
 int /*<<< orphan*/  CACHE_MODE_1 ; 
 int /*<<< orphan*/  GAM_ECOCHK ; 
 int /*<<< orphan*/  GEN6_WIZ_HASHING_16x4 ; 
 int /*<<< orphan*/  GEN6_WIZ_HASHING_MASK ; 
 int /*<<< orphan*/  GEN7_FF_THREAD_MODE ; 
 int GEN7_FF_VS_REF_CNT_FFME ; 
 int /*<<< orphan*/  GEN7_GT_MODE ; 
 int /*<<< orphan*/  GEN7_SQ_CHICKEN_MBCUNIT_CONFIG ; 
 int GEN7_SQ_CHICKEN_MBCUNIT_SQINTMOB ; 
 int /*<<< orphan*/  HALF_SLICE_CHICKEN3 ; 
 int /*<<< orphan*/  HIZ_RAW_STALL_OPT_DISABLE ; 
 int HSW_ECOCHK_ARB_PRIO_SOL ; 
 int /*<<< orphan*/  HSW_ROW_CHICKEN3 ; 
 int /*<<< orphan*/  HSW_ROW_CHICKEN3_L3_GLOBAL_ATOMICS_DISABLE ; 
 int /*<<< orphan*/  HSW_SAMPLE_C_PERFORMANCE ; 
 int /*<<< orphan*/  HSW_SCRATCH1 ; 
 int HSW_SCRATCH1_L3_DATA_ATOMICS_DISABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PIXEL_SUBSPAN_COLLECT_OPT_DISABLE ; 
 int /*<<< orphan*/  RC_OP_FLUSH_ENABLE ; 
 int _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int _MASKED_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpt_init_clock_gating (struct drm_i915_private*) ; 

__attribute__((used)) static void hsw_init_clock_gating(struct drm_i915_private *dev_priv)
{
	/* L3 caching of data atomics doesn't work -- disable it. */
	I915_WRITE(HSW_SCRATCH1, HSW_SCRATCH1_L3_DATA_ATOMICS_DISABLE);
	I915_WRITE(HSW_ROW_CHICKEN3,
		   _MASKED_BIT_ENABLE(HSW_ROW_CHICKEN3_L3_GLOBAL_ATOMICS_DISABLE));

	/* This is required by WaCatErrorRejectionIssue:hsw */
	I915_WRITE(GEN7_SQ_CHICKEN_MBCUNIT_CONFIG,
			I915_READ(GEN7_SQ_CHICKEN_MBCUNIT_CONFIG) |
			GEN7_SQ_CHICKEN_MBCUNIT_SQINTMOB);

	/* WaVSRefCountFullforceMissDisable:hsw */
	I915_WRITE(GEN7_FF_THREAD_MODE,
		   I915_READ(GEN7_FF_THREAD_MODE) & ~GEN7_FF_VS_REF_CNT_FFME);

	/* WaDisable_RenderCache_OperationalFlush:hsw */
	I915_WRITE(CACHE_MODE_0_GEN7, _MASKED_BIT_DISABLE(RC_OP_FLUSH_ENABLE));

	/* enable HiZ Raw Stall Optimization */
	I915_WRITE(CACHE_MODE_0_GEN7,
		   _MASKED_BIT_DISABLE(HIZ_RAW_STALL_OPT_DISABLE));

	/* WaDisable4x2SubspanOptimization:hsw */
	I915_WRITE(CACHE_MODE_1,
		   _MASKED_BIT_ENABLE(PIXEL_SUBSPAN_COLLECT_OPT_DISABLE));

	/*
	 * BSpec recommends 8x4 when MSAA is used,
	 * however in practice 16x4 seems fastest.
	 *
	 * Note that PS/WM thread counts depend on the WIZ hashing
	 * disable bit, which we don't touch here, but it's good
	 * to keep in mind (see 3DSTATE_PS and 3DSTATE_WM).
	 */
	I915_WRITE(GEN7_GT_MODE,
		   _MASKED_FIELD(GEN6_WIZ_HASHING_MASK, GEN6_WIZ_HASHING_16x4));

	/* WaSampleCChickenBitEnable:hsw */
	I915_WRITE(HALF_SLICE_CHICKEN3,
		   _MASKED_BIT_ENABLE(HSW_SAMPLE_C_PERFORMANCE));

	/* WaSwitchSolVfFArbitrationPriority:hsw */
	I915_WRITE(GAM_ECOCHK, I915_READ(GAM_ECOCHK) | HSW_ECOCHK_ARB_PRIO_SOL);

	lpt_init_clock_gating(dev_priv);
}