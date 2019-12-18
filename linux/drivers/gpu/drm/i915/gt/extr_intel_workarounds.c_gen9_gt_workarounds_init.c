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
 int BDW_DISABLE_HDC_INVALIDATION ; 
 int ECOCHK_DIS_TLB ; 
 int /*<<< orphan*/  GAM_ECOCHK ; 
 scalar_t__ HAS_LLC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_COFFEELAKE (struct drm_i915_private*) ; 
 int MMCD_HOTSPOT_EN ; 
 int /*<<< orphan*/  MMCD_MISC_CTRL ; 
 int MMCD_PCLA ; 
 int /*<<< orphan*/  wa_write_or (struct i915_wa_list*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gen9_gt_workarounds_init(struct drm_i915_private *i915, struct i915_wa_list *wal)
{
	/* WaDisableKillLogic:bxt,skl,kbl */
	if (!IS_COFFEELAKE(i915))
		wa_write_or(wal,
			    GAM_ECOCHK,
			    ECOCHK_DIS_TLB);

	if (HAS_LLC(i915)) {
		/* WaCompressedResourceSamplerPbeMediaNewHashMode:skl,kbl
		 *
		 * Must match Display Engine. See
		 * WaCompressedResourceDisplayNewHashMode.
		 */
		wa_write_or(wal,
			    MMCD_MISC_CTRL,
			    MMCD_PCLA | MMCD_HOTSPOT_EN);
	}

	/* WaDisableHDCInvalidation:skl,bxt,kbl,cfl */
	wa_write_or(wal,
		    GAM_ECOCHK,
		    BDW_DISABLE_HDC_INVALIDATION);
}