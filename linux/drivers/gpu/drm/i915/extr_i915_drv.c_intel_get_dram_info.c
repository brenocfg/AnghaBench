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
struct dram_info {int is_16gb_dimm; int /*<<< orphan*/  ranks; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  bandwidth_kbps; } ;
struct drm_i915_private {struct dram_info dram_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int bxt_get_dram_info (struct drm_i915_private*) ; 
 int skl_get_dram_info (struct drm_i915_private*) ; 
 int /*<<< orphan*/  yesno (int) ; 

__attribute__((used)) static void
intel_get_dram_info(struct drm_i915_private *dev_priv)
{
	struct dram_info *dram_info = &dev_priv->dram_info;
	int ret;

	/*
	 * Assume 16Gb DIMMs are present until proven otherwise.
	 * This is only used for the level 0 watermark latency
	 * w/a which does not apply to bxt/glk.
	 */
	dram_info->is_16gb_dimm = !IS_GEN9_LP(dev_priv);

	if (INTEL_GEN(dev_priv) < 9)
		return;

	if (IS_GEN9_LP(dev_priv))
		ret = bxt_get_dram_info(dev_priv);
	else
		ret = skl_get_dram_info(dev_priv);
	if (ret)
		return;

	DRM_DEBUG_KMS("DRAM bandwidth: %u kBps, channels: %u\n",
		      dram_info->bandwidth_kbps,
		      dram_info->num_channels);

	DRM_DEBUG_KMS("DRAM ranks: %u, 16Gb DIMMs: %s\n",
		      dram_info->ranks, yesno(dram_info->is_16gb_dimm));
}