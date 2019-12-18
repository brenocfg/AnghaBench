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
typedef  int u64 ;
typedef  int u32 ;
struct intel_uncore {int dummy; } ;
struct intel_gt {int /*<<< orphan*/  i915; struct intel_uncore* uncore; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FAULT_GTT_SEL ; 
 int FAULT_VA_HIGH_BITS ; 
 int /*<<< orphan*/  GEN12_FAULT_TLB_DATA0 ; 
 int /*<<< orphan*/  GEN12_FAULT_TLB_DATA1 ; 
 int /*<<< orphan*/  GEN12_RING_FAULT_REG ; 
 int /*<<< orphan*/  GEN8_FAULT_TLB_DATA0 ; 
 int /*<<< orphan*/  GEN8_FAULT_TLB_DATA1 ; 
 int /*<<< orphan*/  GEN8_RING_FAULT_ENGINE_ID (int) ; 
 int /*<<< orphan*/  GEN8_RING_FAULT_REG ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_FAULT_FAULT_TYPE (int) ; 
 int /*<<< orphan*/  RING_FAULT_SRCID (int) ; 
 int RING_FAULT_VALID ; 
 int intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static void gen8_check_faults(struct intel_gt *gt)
{
	struct intel_uncore *uncore = gt->uncore;
	i915_reg_t fault_reg, fault_data0_reg, fault_data1_reg;
	u32 fault;

	if (INTEL_GEN(gt->i915) >= 12) {
		fault_reg = GEN12_RING_FAULT_REG;
		fault_data0_reg = GEN12_FAULT_TLB_DATA0;
		fault_data1_reg = GEN12_FAULT_TLB_DATA1;
	} else {
		fault_reg = GEN8_RING_FAULT_REG;
		fault_data0_reg = GEN8_FAULT_TLB_DATA0;
		fault_data1_reg = GEN8_FAULT_TLB_DATA1;
	}

	fault = intel_uncore_read(uncore, fault_reg);
	if (fault & RING_FAULT_VALID) {
		u32 fault_data0, fault_data1;
		u64 fault_addr;

		fault_data0 = intel_uncore_read(uncore, fault_data0_reg);
		fault_data1 = intel_uncore_read(uncore, fault_data1_reg);

		fault_addr = ((u64)(fault_data1 & FAULT_VA_HIGH_BITS) << 44) |
			     ((u64)fault_data0 << 12);

		DRM_DEBUG_DRIVER("Unexpected fault\n"
				 "\tAddr: 0x%08x_%08x\n"
				 "\tAddress space: %s\n"
				 "\tEngine ID: %d\n"
				 "\tSource ID: %d\n"
				 "\tType: %d\n",
				 upper_32_bits(fault_addr),
				 lower_32_bits(fault_addr),
				 fault_data1 & FAULT_GTT_SEL ? "GGTT" : "PPGTT",
				 GEN8_RING_FAULT_ENGINE_ID(fault),
				 RING_FAULT_SRCID(fault),
				 RING_FAULT_FAULT_TYPE(fault));
	}
}