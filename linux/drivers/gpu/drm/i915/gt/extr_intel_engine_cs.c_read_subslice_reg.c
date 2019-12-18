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
struct intel_uncore {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {struct intel_uncore* uncore; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int FW_REG_READ ; 
 int FW_REG_WRITE ; 
 int GEN11_MCR_SLICE (int) ; 
 int GEN11_MCR_SLICE_MASK ; 
 int GEN11_MCR_SUBSLICE (int) ; 
 int GEN11_MCR_SUBSLICE_MASK ; 
 int /*<<< orphan*/  GEN8_MCR_SELECTOR ; 
 int GEN8_MCR_SLICE (int) ; 
 int GEN8_MCR_SLICE_MASK ; 
 int GEN8_MCR_SUBSLICE (int) ; 
 int GEN8_MCR_SUBSLICE_MASK ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int intel_uncore_forcewake_for_reg (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get__locked (struct intel_uncore*,int) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put__locked (struct intel_uncore*,int) ; 
 int intel_uncore_read_fw (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write_fw (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
read_subslice_reg(struct intel_engine_cs *engine, int slice, int subslice,
		  i915_reg_t reg)
{
	struct drm_i915_private *i915 = engine->i915;
	struct intel_uncore *uncore = engine->uncore;
	u32 mcr_mask, mcr_ss, mcr, old_mcr, val;
	enum forcewake_domains fw_domains;

	if (INTEL_GEN(i915) >= 11) {
		mcr_mask = GEN11_MCR_SLICE_MASK | GEN11_MCR_SUBSLICE_MASK;
		mcr_ss = GEN11_MCR_SLICE(slice) | GEN11_MCR_SUBSLICE(subslice);
	} else {
		mcr_mask = GEN8_MCR_SLICE_MASK | GEN8_MCR_SUBSLICE_MASK;
		mcr_ss = GEN8_MCR_SLICE(slice) | GEN8_MCR_SUBSLICE(subslice);
	}

	fw_domains = intel_uncore_forcewake_for_reg(uncore, reg,
						    FW_REG_READ);
	fw_domains |= intel_uncore_forcewake_for_reg(uncore,
						     GEN8_MCR_SELECTOR,
						     FW_REG_READ | FW_REG_WRITE);

	spin_lock_irq(&uncore->lock);
	intel_uncore_forcewake_get__locked(uncore, fw_domains);

	old_mcr = mcr = intel_uncore_read_fw(uncore, GEN8_MCR_SELECTOR);

	mcr &= ~mcr_mask;
	mcr |= mcr_ss;
	intel_uncore_write_fw(uncore, GEN8_MCR_SELECTOR, mcr);

	val = intel_uncore_read_fw(uncore, reg);

	mcr &= ~mcr_mask;
	mcr |= old_mcr & mcr_mask;

	intel_uncore_write_fw(uncore, GEN8_MCR_SELECTOR, mcr);

	intel_uncore_forcewake_put__locked(uncore, fw_domains);
	spin_unlock_irq(&uncore->lock);

	return val;
}