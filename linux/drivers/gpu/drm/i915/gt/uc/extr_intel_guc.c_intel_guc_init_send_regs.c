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
struct TYPE_2__ {unsigned int count; int fw_domains; void* base; } ;
struct intel_guc {TYPE_1__ send_regs; } ;
struct intel_gt {int /*<<< orphan*/  uncore; int /*<<< orphan*/  i915; } ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int FW_REG_READ ; 
 int FW_REG_WRITE ; 
 int /*<<< orphan*/  GEN11_SOFT_SCRATCH (int /*<<< orphan*/ ) ; 
 unsigned int GEN11_SOFT_SCRATCH_COUNT ; 
 scalar_t__ GUC_MAX_MMIO_MSG_LEN ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOFT_SCRATCH (int /*<<< orphan*/ ) ; 
 scalar_t__ SOFT_SCRATCH_COUNT ; 
 int /*<<< orphan*/  guc_send_reg (struct intel_guc*,unsigned int) ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 void* i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int intel_uncore_forcewake_for_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void intel_guc_init_send_regs(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);
	enum forcewake_domains fw_domains = 0;
	unsigned int i;

	if (INTEL_GEN(gt->i915) >= 11) {
		guc->send_regs.base =
				i915_mmio_reg_offset(GEN11_SOFT_SCRATCH(0));
		guc->send_regs.count = GEN11_SOFT_SCRATCH_COUNT;
	} else {
		guc->send_regs.base = i915_mmio_reg_offset(SOFT_SCRATCH(0));
		guc->send_regs.count = GUC_MAX_MMIO_MSG_LEN;
		BUILD_BUG_ON(GUC_MAX_MMIO_MSG_LEN > SOFT_SCRATCH_COUNT);
	}

	for (i = 0; i < guc->send_regs.count; i++) {
		fw_domains |= intel_uncore_forcewake_for_reg(gt->uncore,
					guc_send_reg(guc, i),
					FW_REG_READ | FW_REG_WRITE);
	}
	guc->send_regs.fw_domains = fw_domains;
}