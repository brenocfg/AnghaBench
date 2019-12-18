#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct uc_css_header {int dummy; } ;
struct intel_uncore {int dummy; } ;
struct intel_uc_fw {int ucode_size; int /*<<< orphan*/  type; } ;
struct intel_gt {TYPE_2__* i915; int /*<<< orphan*/  ggtt; struct intel_uncore* uncore; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int DMA_ADDRESS_SPACE_WOPCM ; 
 int /*<<< orphan*/  DMA_ADDR_0_HIGH ; 
 int /*<<< orphan*/  DMA_ADDR_0_LOW ; 
 int /*<<< orphan*/  DMA_ADDR_1_HIGH ; 
 int /*<<< orphan*/  DMA_ADDR_1_LOW ; 
 int /*<<< orphan*/  DMA_COPY_SIZE ; 
 int /*<<< orphan*/  DMA_CTRL ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int START_DMA ; 
 int _MASKED_BIT_DISABLE (int) ; 
 int _MASKED_BIT_ENABLE (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i915_inject_load_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uc_fw_type_repr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_read_fw (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write_fw (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 int intel_wait_for_register_fw (struct intel_uncore*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uc_fw_ggtt_offset (struct intel_uc_fw*,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uc_fw_xfer(struct intel_uc_fw *uc_fw, struct intel_gt *gt,
		      u32 wopcm_offset, u32 dma_flags)
{
	struct intel_uncore *uncore = gt->uncore;
	u64 offset;
	int ret;

	ret = i915_inject_load_error(gt->i915, -ETIMEDOUT);
	if (ret)
		return ret;

	intel_uncore_forcewake_get(uncore, FORCEWAKE_ALL);

	/* Set the source address for the uCode */
	offset = uc_fw_ggtt_offset(uc_fw, gt->ggtt);
	GEM_BUG_ON(upper_32_bits(offset) & 0xFFFF0000);
	intel_uncore_write_fw(uncore, DMA_ADDR_0_LOW, lower_32_bits(offset));
	intel_uncore_write_fw(uncore, DMA_ADDR_0_HIGH, upper_32_bits(offset));

	/* Set the DMA destination */
	intel_uncore_write_fw(uncore, DMA_ADDR_1_LOW, wopcm_offset);
	intel_uncore_write_fw(uncore, DMA_ADDR_1_HIGH, DMA_ADDRESS_SPACE_WOPCM);

	/*
	 * Set the transfer size. The header plus uCode will be copied to WOPCM
	 * via DMA, excluding any other components
	 */
	intel_uncore_write_fw(uncore, DMA_COPY_SIZE,
			      sizeof(struct uc_css_header) + uc_fw->ucode_size);

	/* Start the DMA */
	intel_uncore_write_fw(uncore, DMA_CTRL,
			      _MASKED_BIT_ENABLE(dma_flags | START_DMA));

	/* Wait for DMA to finish */
	ret = intel_wait_for_register_fw(uncore, DMA_CTRL, START_DMA, 0, 100);
	if (ret)
		dev_err(gt->i915->drm.dev, "DMA for %s fw failed, DMA_CTRL=%u\n",
			intel_uc_fw_type_repr(uc_fw->type),
			intel_uncore_read_fw(uncore, DMA_CTRL));

	/* Disable the bits once DMA is over */
	intel_uncore_write_fw(uncore, DMA_CTRL, _MASKED_BIT_DISABLE(dma_flags));

	intel_uncore_forcewake_put(uncore, FORCEWAKE_ALL);

	return ret;
}