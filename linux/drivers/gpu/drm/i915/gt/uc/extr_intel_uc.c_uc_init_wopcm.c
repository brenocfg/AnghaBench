#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_uncore {int dummy; } ;
struct intel_uc {int dummy; } ;
struct intel_gt {TYPE_1__* i915; struct intel_uncore* uncore; } ;
struct TYPE_3__ {int /*<<< orphan*/  wopcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_GUC_WOPCM_OFFSET ; 
 int E2BIG ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GUC_WOPCM_OFFSET_MASK ; 
 int GUC_WOPCM_OFFSET_VALID ; 
 int /*<<< orphan*/  GUC_WOPCM_SIZE ; 
 int GUC_WOPCM_SIZE_LOCKED ; 
 int GUC_WOPCM_SIZE_MASK ; 
 int HUC_LOADING_AGENT_GUC ; 
 int i915_inject_load_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_probe_error (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  intel_uc_supports_guc (struct intel_uc*) ; 
 scalar_t__ intel_uc_uses_huc (struct intel_uc*) ; 
 int /*<<< orphan*/  intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int intel_uncore_write_and_verify (struct intel_uncore*,int /*<<< orphan*/ ,int,int,int) ; 
 int intel_wopcm_guc_base (int /*<<< orphan*/ *) ; 
 int intel_wopcm_guc_size (int /*<<< orphan*/ *) ; 
 struct intel_gt* uc_to_gt (struct intel_uc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int uc_init_wopcm(struct intel_uc *uc)
{
	struct intel_gt *gt = uc_to_gt(uc);
	struct intel_uncore *uncore = gt->uncore;
	u32 base = intel_wopcm_guc_base(&gt->i915->wopcm);
	u32 size = intel_wopcm_guc_size(&gt->i915->wopcm);
	u32 huc_agent = intel_uc_uses_huc(uc) ? HUC_LOADING_AGENT_GUC : 0;
	u32 mask;
	int err;

	if (unlikely(!base || !size)) {
		i915_probe_error(gt->i915, "Unsuccessful WOPCM partitioning\n");
		return -E2BIG;
	}

	GEM_BUG_ON(!intel_uc_supports_guc(uc));
	GEM_BUG_ON(!(base & GUC_WOPCM_OFFSET_MASK));
	GEM_BUG_ON(base & ~GUC_WOPCM_OFFSET_MASK);
	GEM_BUG_ON(!(size & GUC_WOPCM_SIZE_MASK));
	GEM_BUG_ON(size & ~GUC_WOPCM_SIZE_MASK);

	err = i915_inject_load_error(gt->i915, -ENXIO);
	if (err)
		return err;

	mask = GUC_WOPCM_SIZE_MASK | GUC_WOPCM_SIZE_LOCKED;
	err = intel_uncore_write_and_verify(uncore, GUC_WOPCM_SIZE, size, mask,
					    size | GUC_WOPCM_SIZE_LOCKED);
	if (err)
		goto err_out;

	mask = GUC_WOPCM_OFFSET_MASK | GUC_WOPCM_OFFSET_VALID | huc_agent;
	err = intel_uncore_write_and_verify(uncore, DMA_GUC_WOPCM_OFFSET,
					    base | huc_agent, mask,
					    base | huc_agent |
					    GUC_WOPCM_OFFSET_VALID);
	if (err)
		goto err_out;

	return 0;

err_out:
	i915_probe_error(gt->i915, "Failed to init uC WOPCM registers!\n");
	i915_probe_error(gt->i915, "%s(%#x)=%#x\n", "DMA_GUC_WOPCM_OFFSET",
			 i915_mmio_reg_offset(DMA_GUC_WOPCM_OFFSET),
			 intel_uncore_read(uncore, DMA_GUC_WOPCM_OFFSET));
	i915_probe_error(gt->i915, "%s(%#x)=%#x\n", "GUC_WOPCM_SIZE",
			 i915_mmio_reg_offset(GUC_WOPCM_SIZE),
			 intel_uncore_read(uncore, GUC_WOPCM_SIZE));

	return err;
}