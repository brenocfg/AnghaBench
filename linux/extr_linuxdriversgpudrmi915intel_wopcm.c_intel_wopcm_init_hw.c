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
struct TYPE_2__ {int size; int base; } ;
struct intel_wopcm {TYPE_1__ guc; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_GUC_WOPCM_OFFSET ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GUC_WOPCM_OFFSET_MASK ; 
 int GUC_WOPCM_OFFSET_VALID ; 
 int /*<<< orphan*/  GUC_WOPCM_SIZE ; 
 int GUC_WOPCM_SIZE_LOCKED ; 
 int GUC_WOPCM_SIZE_MASK ; 
 int /*<<< orphan*/  HAS_GUC (struct drm_i915_private*) ; 
 int HUC_LOADING_AGENT_GUC ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USES_GUC (struct drm_i915_private*) ; 
 scalar_t__ USES_HUC (struct drm_i915_private*) ; 
 struct drm_i915_private* wopcm_to_i915 (struct intel_wopcm*) ; 
 int write_and_verify (struct drm_i915_private*,int /*<<< orphan*/ ,int,int,int) ; 

int intel_wopcm_init_hw(struct intel_wopcm *wopcm)
{
	struct drm_i915_private *dev_priv = wopcm_to_i915(wopcm);
	u32 huc_agent;
	u32 mask;
	int err;

	if (!USES_GUC(dev_priv))
		return 0;

	GEM_BUG_ON(!HAS_GUC(dev_priv));
	GEM_BUG_ON(!wopcm->guc.size);
	GEM_BUG_ON(!wopcm->guc.base);

	err = write_and_verify(dev_priv, GUC_WOPCM_SIZE, wopcm->guc.size,
			       GUC_WOPCM_SIZE_MASK | GUC_WOPCM_SIZE_LOCKED,
			       GUC_WOPCM_SIZE_LOCKED);
	if (err)
		goto err_out;

	huc_agent = USES_HUC(dev_priv) ? HUC_LOADING_AGENT_GUC : 0;
	mask = GUC_WOPCM_OFFSET_MASK | GUC_WOPCM_OFFSET_VALID | huc_agent;
	err = write_and_verify(dev_priv, DMA_GUC_WOPCM_OFFSET,
			       wopcm->guc.base | huc_agent, mask,
			       GUC_WOPCM_OFFSET_VALID);
	if (err)
		goto err_out;

	return 0;

err_out:
	DRM_ERROR("Failed to init WOPCM registers:\n");
	DRM_ERROR("DMA_GUC_WOPCM_OFFSET=%#x\n",
		  I915_READ(DMA_GUC_WOPCM_OFFSET));
	DRM_ERROR("GUC_WOPCM_SIZE=%#x\n", I915_READ(GUC_WOPCM_SIZE));

	return err;
}