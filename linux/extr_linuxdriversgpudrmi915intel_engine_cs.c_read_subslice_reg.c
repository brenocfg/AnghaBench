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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;
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
 int I915_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int intel_calculate_mcr_s_ss_select (struct drm_i915_private*) ; 
 int intel_uncore_forcewake_for_reg (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get__locked (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put__locked (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint32_t
read_subslice_reg(struct drm_i915_private *dev_priv, int slice,
		  int subslice, i915_reg_t reg)
{
	uint32_t mcr_slice_subslice_mask;
	uint32_t mcr_slice_subslice_select;
	uint32_t default_mcr_s_ss_select;
	uint32_t mcr;
	uint32_t ret;
	enum forcewake_domains fw_domains;

	if (INTEL_GEN(dev_priv) >= 11) {
		mcr_slice_subslice_mask = GEN11_MCR_SLICE_MASK |
					  GEN11_MCR_SUBSLICE_MASK;
		mcr_slice_subslice_select = GEN11_MCR_SLICE(slice) |
					    GEN11_MCR_SUBSLICE(subslice);
	} else {
		mcr_slice_subslice_mask = GEN8_MCR_SLICE_MASK |
					  GEN8_MCR_SUBSLICE_MASK;
		mcr_slice_subslice_select = GEN8_MCR_SLICE(slice) |
					    GEN8_MCR_SUBSLICE(subslice);
	}

	default_mcr_s_ss_select = intel_calculate_mcr_s_ss_select(dev_priv);

	fw_domains = intel_uncore_forcewake_for_reg(dev_priv, reg,
						    FW_REG_READ);
	fw_domains |= intel_uncore_forcewake_for_reg(dev_priv,
						     GEN8_MCR_SELECTOR,
						     FW_REG_READ | FW_REG_WRITE);

	spin_lock_irq(&dev_priv->uncore.lock);
	intel_uncore_forcewake_get__locked(dev_priv, fw_domains);

	mcr = I915_READ_FW(GEN8_MCR_SELECTOR);

	WARN_ON_ONCE((mcr & mcr_slice_subslice_mask) !=
		     default_mcr_s_ss_select);

	mcr &= ~mcr_slice_subslice_mask;
	mcr |= mcr_slice_subslice_select;
	I915_WRITE_FW(GEN8_MCR_SELECTOR, mcr);

	ret = I915_READ_FW(reg);

	mcr &= ~mcr_slice_subslice_mask;
	mcr |= default_mcr_s_ss_select;

	I915_WRITE_FW(GEN8_MCR_SELECTOR, mcr);

	intel_uncore_forcewake_put__locked(dev_priv, fw_domains);
	spin_unlock_irq(&dev_priv->uncore.lock);

	return ret;
}