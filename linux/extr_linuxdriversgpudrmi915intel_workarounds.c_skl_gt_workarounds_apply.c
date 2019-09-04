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
 int GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS ; 
 int /*<<< orphan*/  GEN7_UCGCTL4 ; 
 int GEN8_EU_GAUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  GEN8_GARBCNTL ; 
 int /*<<< orphan*/  GEN9_GAMT_ECO_REG_RW_IA ; 
 int GEN9_GAPS_TSV_CREDIT_DISABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_SKL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REVID_FOREVER ; 
 int /*<<< orphan*/  SKL_REVID_H0 ; 
 int /*<<< orphan*/  gen9_gt_workarounds_apply (struct drm_i915_private*) ; 

__attribute__((used)) static void skl_gt_workarounds_apply(struct drm_i915_private *dev_priv)
{
	gen9_gt_workarounds_apply(dev_priv);

	/* WaEnableGapsTsvCreditFix:skl */
	I915_WRITE(GEN8_GARBCNTL,
		   I915_READ(GEN8_GARBCNTL) | GEN9_GAPS_TSV_CREDIT_DISABLE);

	/* WaDisableGafsUnitClkGating:skl */
	I915_WRITE(GEN7_UCGCTL4,
		   I915_READ(GEN7_UCGCTL4) | GEN8_EU_GAUNIT_CLOCK_GATE_DISABLE);

	/* WaInPlaceDecompressionHang:skl */
	if (IS_SKL_REVID(dev_priv, SKL_REVID_H0, REVID_FOREVER))
		I915_WRITE(GEN9_GAMT_ECO_REG_RW_IA,
			   I915_READ(GEN9_GAMT_ECO_REG_RW_IA) |
			   GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);
}