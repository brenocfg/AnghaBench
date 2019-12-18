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
struct intel_uncore {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN7_MISCCPCTL ; 
 int /*<<< orphan*/  GEN8_DOP_CLOCK_GATE_GUC_ENABLE ; 
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
 scalar_t__ IS_GEN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN9_LP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_rmw (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void guc_prepare_xfer(struct intel_uncore *uncore)
{
	u32 shim_flags = GUC_DISABLE_SRAM_INIT_TO_ZEROES |
			 GUC_ENABLE_READ_CACHE_LOGIC |
			 GUC_ENABLE_MIA_CACHING |
			 GUC_ENABLE_READ_CACHE_FOR_SRAM_DATA |
			 GUC_ENABLE_READ_CACHE_FOR_WOPCM_DATA |
			 GUC_ENABLE_MIA_CLOCK_GATING;

	/* Must program this register before loading the ucode with DMA */
	intel_uncore_write(uncore, GUC_SHIM_CONTROL, shim_flags);

	if (IS_GEN9_LP(uncore->i915))
		intel_uncore_write(uncore, GEN9LP_GT_PM_CONFIG, GT_DOORBELL_ENABLE);
	else
		intel_uncore_write(uncore, GEN9_GT_PM_CONFIG, GT_DOORBELL_ENABLE);

	if (IS_GEN(uncore->i915, 9)) {
		/* DOP Clock Gating Enable for GuC clocks */
		intel_uncore_rmw(uncore, GEN7_MISCCPCTL,
				 0, GEN8_DOP_CLOCK_GATE_GUC_ENABLE);

		/* allows for 5us (in 10ns units) before GT can go to RC6 */
		intel_uncore_write(uncore, GUC_ARAT_C6DIS, 0x1FF);
	}
}