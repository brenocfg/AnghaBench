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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct intel_uncore {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {scalar_t__* cur_residency; scalar_t__* prev_hw_residency; } ;
struct TYPE_4__ {TYPE_1__ rc6; } ;
struct drm_i915_private {int czclk_freq; TYPE_2__ gt_pm; struct intel_uncore uncore; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ BIT_ULL (int) ; 
 int /*<<< orphan*/  FW_REG_READ ; 
 int /*<<< orphan*/  const GEN6_GT_GFX_RC6_LOCKED ; 
 int /*<<< orphan*/  HAS_RC6 (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int i915_mmio_reg_offset (int /*<<< orphan*/  const) ; 
 unsigned int intel_uncore_forcewake_for_reg (struct intel_uncore*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get__locked (struct intel_uncore*,unsigned int) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put__locked (struct intel_uncore*,unsigned int) ; 
 scalar_t__ intel_uncore_read_fw (struct intel_uncore*,int /*<<< orphan*/  const) ; 
 scalar_t__ mul_u64_u32_div (scalar_t__,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ vlv_residency_raw (struct drm_i915_private*,int /*<<< orphan*/  const) ; 

u64 intel_rc6_residency_ns(struct drm_i915_private *dev_priv,
			   const i915_reg_t reg)
{
	struct intel_uncore *uncore = &dev_priv->uncore;
	u64 time_hw, prev_hw, overflow_hw;
	unsigned int fw_domains;
	unsigned long flags;
	unsigned int i;
	u32 mul, div;

	if (!HAS_RC6(dev_priv))
		return 0;

	/*
	 * Store previous hw counter values for counter wrap-around handling.
	 *
	 * There are only four interesting registers and they live next to each
	 * other so we can use the relative address, compared to the smallest
	 * one as the index into driver storage.
	 */
	i = (i915_mmio_reg_offset(reg) -
	     i915_mmio_reg_offset(GEN6_GT_GFX_RC6_LOCKED)) / sizeof(u32);
	if (WARN_ON_ONCE(i >= ARRAY_SIZE(dev_priv->gt_pm.rc6.cur_residency)))
		return 0;

	fw_domains = intel_uncore_forcewake_for_reg(uncore, reg, FW_REG_READ);

	spin_lock_irqsave(&uncore->lock, flags);
	intel_uncore_forcewake_get__locked(uncore, fw_domains);

	/* On VLV and CHV, residency time is in CZ units rather than 1.28us */
	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		mul = 1000000;
		div = dev_priv->czclk_freq;
		overflow_hw = BIT_ULL(40);
		time_hw = vlv_residency_raw(dev_priv, reg);
	} else {
		/* 833.33ns units on Gen9LP, 1.28us elsewhere. */
		if (IS_GEN9_LP(dev_priv)) {
			mul = 10000;
			div = 12;
		} else {
			mul = 1280;
			div = 1;
		}

		overflow_hw = BIT_ULL(32);
		time_hw = intel_uncore_read_fw(uncore, reg);
	}

	/*
	 * Counter wrap handling.
	 *
	 * But relying on a sufficient frequency of queries otherwise counters
	 * can still wrap.
	 */
	prev_hw = dev_priv->gt_pm.rc6.prev_hw_residency[i];
	dev_priv->gt_pm.rc6.prev_hw_residency[i] = time_hw;

	/* RC6 delta from last sample. */
	if (time_hw >= prev_hw)
		time_hw -= prev_hw;
	else
		time_hw += overflow_hw - prev_hw;

	/* Add delta to RC6 extended raw driver copy. */
	time_hw += dev_priv->gt_pm.rc6.cur_residency[i];
	dev_priv->gt_pm.rc6.cur_residency[i] = time_hw;

	intel_uncore_forcewake_put__locked(uncore, fw_domains);
	spin_unlock_irqrestore(&uncore->lock, flags);

	return mul_u64_u32_div(time_hw, mul, div);
}