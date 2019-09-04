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
struct TYPE_2__ {unsigned int count; int fw_domains; int /*<<< orphan*/  base; } ;
struct intel_guc {TYPE_1__ send_regs; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int FW_REG_READ ; 
 int FW_REG_WRITE ; 
 int /*<<< orphan*/  SOFT_SCRATCH (int /*<<< orphan*/ ) ; 
 unsigned int SOFT_SCRATCH_COUNT ; 
 int /*<<< orphan*/  guc_send_reg (struct intel_guc*,unsigned int) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int intel_uncore_forcewake_for_reg (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 

void intel_guc_init_send_regs(struct intel_guc *guc)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	enum forcewake_domains fw_domains = 0;
	unsigned int i;

	guc->send_regs.base = i915_mmio_reg_offset(SOFT_SCRATCH(0));
	guc->send_regs.count = SOFT_SCRATCH_COUNT - 1;

	for (i = 0; i < guc->send_regs.count; i++) {
		fw_domains |= intel_uncore_forcewake_for_reg(dev_priv,
					guc_send_reg(guc, i),
					FW_REG_READ | FW_REG_WRITE);
	}
	guc->send_regs.fw_domains = fw_domains;
}