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
 int /*<<< orphan*/  CNL_REVID_B0 ; 
 int /*<<< orphan*/  GAMT_CHKN_BIT_REG ; 
 int GAMT_CHKN_DISABLE_I2M_CYCLE_ON_WR_PORT ; 
 int GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS ; 
 int /*<<< orphan*/  GEN7_FF_SLICE_CS_CHICKEN1 ; 
 int /*<<< orphan*/  GEN9_FFSC_PERCTX_PREEMPT_CTRL ; 
 int /*<<< orphan*/  GEN9_GAMT_ECO_REG_RW_IA ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_CNL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wa_init_mcr (struct drm_i915_private*) ; 

__attribute__((used)) static void cnl_gt_workarounds_apply(struct drm_i915_private *dev_priv)
{
	wa_init_mcr(dev_priv);

	/* WaDisableI2mCycleOnWRPort:cnl (pre-prod) */
	if (IS_CNL_REVID(dev_priv, CNL_REVID_B0, CNL_REVID_B0))
		I915_WRITE(GAMT_CHKN_BIT_REG,
			   I915_READ(GAMT_CHKN_BIT_REG) |
			   GAMT_CHKN_DISABLE_I2M_CYCLE_ON_WR_PORT);

	/* WaInPlaceDecompressionHang:cnl */
	I915_WRITE(GEN9_GAMT_ECO_REG_RW_IA,
		   I915_READ(GEN9_GAMT_ECO_REG_RW_IA) |
		   GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);

	/* WaEnablePreemptionGranularityControlByUMD:cnl */
	I915_WRITE(GEN7_FF_SLICE_CS_CHICKEN1,
		   _MASKED_BIT_ENABLE(GEN9_FFSC_PERCTX_PREEMPT_CTRL));
}