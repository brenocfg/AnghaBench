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

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int E2BIG ; 
 int GUC_WOPCM_RESERVED ; 

__attribute__((used)) static inline int gen9_check_huc_fw_fits(u32 guc_wopcm_size, u32 huc_fw_size)
{
	/*
	 * On Gen9 & CNL A0, hardware requires the total available GuC WOPCM
	 * size to be larger than or equal to HuC firmware size. Otherwise,
	 * firmware uploading would fail.
	 */
	if (huc_fw_size > guc_wopcm_size - GUC_WOPCM_RESERVED) {
		DRM_ERROR("HuC FW (%uKiB) won't fit in GuC WOPCM (%uKiB).\n",
			  huc_fw_size / 1024,
			  (guc_wopcm_size - GUC_WOPCM_RESERVED) / 1024);
		return -E2BIG;
	}

	return 0;
}