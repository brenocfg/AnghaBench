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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__,scalar_t__) ; 
 int E2BIG ; 
 scalar_t__ GEN9_GUC_WOPCM_OFFSET ; 

__attribute__((used)) static inline int gen9_check_dword_gap(u32 guc_wopcm_base, u32 guc_wopcm_size)
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
		DRM_ERROR("GuC WOPCM size %uKiB is too small. %uKiB needed.\n",
			  guc_wopcm_size / 1024,
			  (u32)(offset + sizeof(u32)) / 1024);
		return -E2BIG;
	}

	return 0;
}