#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int GUC_WOPCM_RESERVED ; 
 int /*<<< orphan*/  INTEL_UC_FW_TYPE_HUC ; 
 int SZ_1K ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  intel_uc_fw_type_repr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool gen9_check_huc_fw_fits(struct drm_i915_private *i915,
					  u32 guc_wopcm_size, u32 huc_fw_size)
{
	/*
	 * On Gen9 & CNL A0, hardware requires the total available GuC WOPCM
	 * size to be larger than or equal to HuC firmware size. Otherwise,
	 * firmware uploading would fail.
	 */
	if (huc_fw_size > guc_wopcm_size - GUC_WOPCM_RESERVED) {
		dev_err(i915->drm.dev, "WOPCM: no space for %s: %uK < %uK\n",
			intel_uc_fw_type_repr(INTEL_UC_FW_TYPE_HUC),
			(guc_wopcm_size - GUC_WOPCM_RESERVED) / SZ_1K,
			huc_fw_size / 1024);
		return false;
	}

	return true;
}