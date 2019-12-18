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
typedef  int /*<<< orphan*/  u32 ;
struct dram_info {scalar_t__ num_channels; int ranks; int is_16gb_dimm; int /*<<< orphan*/  symmetric_memory; } ;
struct drm_i915_private {struct dram_info dram_info; } ;
struct dram_channel_info {int ranks; scalar_t__ is_16gb_dimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKL_MAD_DIMM_CH0_0_0_0_MCHBAR_MCMAIN ; 
 int /*<<< orphan*/  SKL_MAD_DIMM_CH1_0_0_0_MCHBAR_MCMAIN ; 
 int /*<<< orphan*/  intel_is_dram_symmetric (struct dram_channel_info*,struct dram_channel_info*) ; 
 int max (int,int) ; 
 int skl_dram_get_channel_info (struct drm_i915_private*,struct dram_channel_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
skl_dram_get_channels_info(struct drm_i915_private *dev_priv)
{
	struct dram_info *dram_info = &dev_priv->dram_info;
	struct dram_channel_info ch0 = {}, ch1 = {};
	u32 val;
	int ret;

	val = I915_READ(SKL_MAD_DIMM_CH0_0_0_0_MCHBAR_MCMAIN);
	ret = skl_dram_get_channel_info(dev_priv, &ch0, 0, val);
	if (ret == 0)
		dram_info->num_channels++;

	val = I915_READ(SKL_MAD_DIMM_CH1_0_0_0_MCHBAR_MCMAIN);
	ret = skl_dram_get_channel_info(dev_priv, &ch1, 1, val);
	if (ret == 0)
		dram_info->num_channels++;

	if (dram_info->num_channels == 0) {
		DRM_INFO("Number of memory channels is zero\n");
		return -EINVAL;
	}

	/*
	 * If any of the channel is single rank channel, worst case output
	 * will be same as if single rank memory, so consider single rank
	 * memory.
	 */
	if (ch0.ranks == 1 || ch1.ranks == 1)
		dram_info->ranks = 1;
	else
		dram_info->ranks = max(ch0.ranks, ch1.ranks);

	if (dram_info->ranks == 0) {
		DRM_INFO("couldn't get memory rank information\n");
		return -EINVAL;
	}

	dram_info->is_16gb_dimm = ch0.is_16gb_dimm || ch1.is_16gb_dimm;

	dram_info->symmetric_memory = intel_is_dram_symmetric(&ch0, &ch1);

	DRM_DEBUG_KMS("Memory configuration is symmetric? %s\n",
		      yesno(dram_info->symmetric_memory));
	return 0;
}