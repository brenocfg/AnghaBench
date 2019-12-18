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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 scalar_t__ GEN9_GUC_WOPCM_OFFSET ; 
 scalar_t__ SZ_1K ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline bool gen9_check_dword_gap(struct drm_i915_private *i915,
					u32 guc_wopcm_base, u32 guc_wopcm_size)
{
	u32 offset;

	/*
	 * GuC WOPCM size shall be at least a dword larger than the offset from
	 * WOPCM base (GuC WOPCM offset from WOPCM base + GEN9_GUC_WOPCM_OFFSET)
	 * due to hardware limitation on Gen9.
	 */
	offset = guc_wopcm_base + GEN9_GUC_WOPCM_OFFSET;
	if (offset > guc_wopcm_size ||
	    (guc_wopcm_size - offset) < sizeof(u32)) {
		dev_err(i915->drm.dev,
			"WOPCM: invalid GuC region size: %uK < %uK\n",
			guc_wopcm_size / SZ_1K,
			(u32)(offset + sizeof(u32)) / SZ_1K);
		return false;
	}

	return true;
}