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
struct intel_guc {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN7_MISCCPCTL ; 
 int GEN8_DOP_CLOCK_GATE_GUC_ENABLE ; 
 int /*<<< orphan*/  GEN9LP_GT_PM_CONFIG ; 
 int /*<<< orphan*/  GEN9_GT_PM_CONFIG ; 
 int GT_DOORBELL_ENABLE ; 
 int /*<<< orphan*/  GUC_ARAT_C6DIS ; 
 int GUC_DISABLE_SRAM_INIT_TO_ZEROES ; 
 int GUC_ENABLE_MIA_CACHING ; 
 int GUC_ENABLE_MIA_CLOCK_GATING ; 
 int GUC_ENABLE_READ_CACHE_FOR_SRAM_DATA ; 
 int GUC_ENABLE_READ_CACHE_FOR_WOPCM_DATA ; 
 int GUC_ENABLE_READ_CACHE_LOGIC ; 
 int /*<<< orphan*/  GUC_SHIM_CONTROL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN9 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 

__attribute__((used)) static void guc_prepare_xfer(struct intel_guc *guc)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);

	/* Must program this register before loading the ucode with DMA */
	I915_WRITE(GUC_SHIM_CONTROL, GUC_DISABLE_SRAM_INIT_TO_ZEROES |
				     GUC_ENABLE_READ_CACHE_LOGIC |
				     GUC_ENABLE_MIA_CACHING |
				     GUC_ENABLE_READ_CACHE_FOR_SRAM_DATA |
				     GUC_ENABLE_READ_CACHE_FOR_WOPCM_DATA |
				     GUC_ENABLE_MIA_CLOCK_GATING);

	if (IS_GEN9_LP(dev_priv))
		I915_WRITE(GEN9LP_GT_PM_CONFIG, GT_DOORBELL_ENABLE);
	else
		I915_WRITE(GEN9_GT_PM_CONFIG, GT_DOORBELL_ENABLE);

	if (IS_GEN9(dev_priv)) {
		/* DOP Clock Gating Enable for GuC clocks */
		I915_WRITE(GEN7_MISCCPCTL, (GEN8_DOP_CLOCK_GATE_GUC_ENABLE |
					    I915_READ(GEN7_MISCCPCTL)));

		/* allows for 5us (in 10ns units) before GT can go to RC6 */
		I915_WRITE(GUC_ARAT_C6DIS, 0x1FF);
	}
}