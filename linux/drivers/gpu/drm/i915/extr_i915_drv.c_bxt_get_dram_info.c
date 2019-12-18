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
typedef  int u8 ;
typedef  int u32 ;
struct dram_info {int bandwidth_kbps; int type; int ranks; int valid; int /*<<< orphan*/  num_channels; } ;
struct drm_i915_private {struct dram_info dram_info; } ;
struct dram_dimm_info {int ranks; int /*<<< orphan*/  width; int /*<<< orphan*/  size; } ;
typedef  enum intel_dram_type { ____Placeholder_intel_dram_type } intel_dram_type ;

/* Variables and functions */
 int BXT_DRAM_CHANNEL_ACTIVE_MASK ; 
 int /*<<< orphan*/  BXT_D_CR_DRP0_DUNIT (int) ; 
 int BXT_D_CR_DRP0_DUNIT_END ; 
 int BXT_D_CR_DRP0_DUNIT_START ; 
 int BXT_MEMORY_FREQ_MULTIPLIER_HZ ; 
 int /*<<< orphan*/  BXT_P_CR_MC_BIOS_REQ_0_0_0 ; 
 int BXT_REQ_DATA_MASK ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int EINVAL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_DRAM_UNKNOWN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bxt_get_dimm_info (struct dram_dimm_info*,int) ; 
 int bxt_get_dimm_type (int) ; 
 int hweight32 (int) ; 
 int /*<<< orphan*/  intel_dram_type_str (int) ; 

__attribute__((used)) static int
bxt_get_dram_info(struct drm_i915_private *dev_priv)
{
	struct dram_info *dram_info = &dev_priv->dram_info;
	u32 dram_channels;
	u32 mem_freq_khz, val;
	u8 num_active_channels;
	int i;

	val = I915_READ(BXT_P_CR_MC_BIOS_REQ_0_0_0);
	mem_freq_khz = DIV_ROUND_UP((val & BXT_REQ_DATA_MASK) *
				    BXT_MEMORY_FREQ_MULTIPLIER_HZ, 1000);

	dram_channels = val & BXT_DRAM_CHANNEL_ACTIVE_MASK;
	num_active_channels = hweight32(dram_channels);

	/* Each active bit represents 4-byte channel */
	dram_info->bandwidth_kbps = (mem_freq_khz * num_active_channels * 4);

	if (dram_info->bandwidth_kbps == 0) {
		DRM_INFO("Couldn't get system memory bandwidth\n");
		return -EINVAL;
	}

	/*
	 * Now read each DUNIT8/9/10/11 to check the rank of each dimms.
	 */
	for (i = BXT_D_CR_DRP0_DUNIT_START; i <= BXT_D_CR_DRP0_DUNIT_END; i++) {
		struct dram_dimm_info dimm;
		enum intel_dram_type type;

		val = I915_READ(BXT_D_CR_DRP0_DUNIT(i));
		if (val == 0xFFFFFFFF)
			continue;

		dram_info->num_channels++;

		bxt_get_dimm_info(&dimm, val);
		type = bxt_get_dimm_type(val);

		WARN_ON(type != INTEL_DRAM_UNKNOWN &&
			dram_info->type != INTEL_DRAM_UNKNOWN &&
			dram_info->type != type);

		DRM_DEBUG_KMS("CH%u DIMM size: %u GB, width: X%u, ranks: %u, type: %s\n",
			      i - BXT_D_CR_DRP0_DUNIT_START,
			      dimm.size, dimm.width, dimm.ranks,
			      intel_dram_type_str(type));

		/*
		 * If any of the channel is single rank channel,
		 * worst case output will be same as if single rank
		 * memory, so consider single rank memory.
		 */
		if (dram_info->ranks == 0)
			dram_info->ranks = dimm.ranks;
		else if (dimm.ranks == 1)
			dram_info->ranks = 1;

		if (type != INTEL_DRAM_UNKNOWN)
			dram_info->type = type;
	}

	if (dram_info->type == INTEL_DRAM_UNKNOWN ||
	    dram_info->ranks == 0) {
		DRM_INFO("couldn't get memory information\n");
		return -EINVAL;
	}

	dram_info->valid = true;
	return 0;
}