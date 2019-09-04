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
struct intel_uc_fw {int header_size; int ucode_size; unsigned long header_offset; } ;
struct intel_guc {struct intel_uc_fw fw; } ;
struct i915_vma {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int DMA_ADDRESS_SPACE_WOPCM ; 
 int /*<<< orphan*/  DMA_ADDR_0_HIGH ; 
 int /*<<< orphan*/  DMA_ADDR_0_LOW ; 
 int /*<<< orphan*/  DMA_ADDR_1_HIGH ; 
 int /*<<< orphan*/  DMA_ADDR_1_LOW ; 
 int /*<<< orphan*/  DMA_COPY_SIZE ; 
 int /*<<< orphan*/  DMA_CTRL ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int START_DMA ; 
 int UOS_MOVE ; 
 int _MASKED_BIT_ENABLE (int) ; 
 int __intel_wait_for_register_fw (struct drm_i915_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 unsigned long intel_guc_ggtt_offset (struct intel_guc*,struct i915_vma*) ; 
 int lower_32_bits (unsigned long) ; 
 int upper_32_bits (unsigned long) ; 

__attribute__((used)) static int guc_xfer_ucode(struct intel_guc *guc, struct i915_vma *vma)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	struct intel_uc_fw *guc_fw = &guc->fw;
	unsigned long offset;
	u32 status;
	int ret;

	/*
	 * The header plus uCode will be copied to WOPCM via DMA, excluding any
	 * other components
	 */
	I915_WRITE(DMA_COPY_SIZE, guc_fw->header_size + guc_fw->ucode_size);

	/* Set the source address for the new blob */
	offset = intel_guc_ggtt_offset(guc, vma) + guc_fw->header_offset;
	I915_WRITE(DMA_ADDR_0_LOW, lower_32_bits(offset));
	I915_WRITE(DMA_ADDR_0_HIGH, upper_32_bits(offset) & 0xFFFF);

	/*
	 * Set the DMA destination. Current uCode expects the code to be
	 * loaded at 8k; locations below this are used for the stack.
	 */
	I915_WRITE(DMA_ADDR_1_LOW, 0x2000);
	I915_WRITE(DMA_ADDR_1_HIGH, DMA_ADDRESS_SPACE_WOPCM);

	/* Finally start the DMA */
	I915_WRITE(DMA_CTRL, _MASKED_BIT_ENABLE(UOS_MOVE | START_DMA));

	/* Wait for DMA to finish */
	ret = __intel_wait_for_register_fw(dev_priv, DMA_CTRL, START_DMA, 0,
					   2, 100, &status);
	DRM_DEBUG_DRIVER("GuC DMA status %#x\n", status);

	return ret;
}