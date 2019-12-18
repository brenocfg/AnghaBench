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
struct i915_wa_list {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS ; 
 int /*<<< orphan*/  GEN7_UCGCTL4 ; 
 int /*<<< orphan*/  GEN8_EU_GAUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  GEN9_GAMT_ECO_REG_RW_IA ; 
 scalar_t__ IS_SKL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REVID_FOREVER ; 
 int /*<<< orphan*/  SKL_REVID_H0 ; 
 int /*<<< orphan*/  gen9_gt_workarounds_init (struct drm_i915_private*,struct i915_wa_list*) ; 
 int /*<<< orphan*/  wa_write_or (struct i915_wa_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
skl_gt_workarounds_init(struct drm_i915_private *i915, struct i915_wa_list *wal)
{
	gen9_gt_workarounds_init(i915, wal);

	/* WaDisableGafsUnitClkGating:skl */
	wa_write_or(wal,
		    GEN7_UCGCTL4,
		    GEN8_EU_GAUNIT_CLOCK_GATE_DISABLE);

	/* WaInPlaceDecompressionHang:skl */
	if (IS_SKL_REVID(i915, SKL_REVID_H0, REVID_FOREVER))
		wa_write_or(wal,
			    GEN9_GAMT_ECO_REG_RW_IA,
			    GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);
}