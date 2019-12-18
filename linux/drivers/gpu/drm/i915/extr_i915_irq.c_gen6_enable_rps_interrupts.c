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
struct intel_rps {int interrupts_enabled; int pm_iir; } ;
struct intel_gt {int /*<<< orphan*/  irq_lock; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {int pm_rps_events; TYPE_1__ gt_pm; struct intel_gt gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_GTPM ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ READ_ONCE (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int gen11_gt_reset_one_iir (struct intel_gt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen6_gt_pm_enable_irq (struct intel_gt*,int) ; 
 int /*<<< orphan*/  gen6_pm_iir (struct drm_i915_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gen6_enable_rps_interrupts(struct drm_i915_private *dev_priv)
{
	struct intel_gt *gt = &dev_priv->gt;
	struct intel_rps *rps = &dev_priv->gt_pm.rps;

	if (READ_ONCE(rps->interrupts_enabled))
		return;

	spin_lock_irq(&gt->irq_lock);
	WARN_ON_ONCE(rps->pm_iir);

	if (INTEL_GEN(dev_priv) >= 11)
		WARN_ON_ONCE(gen11_gt_reset_one_iir(gt, 0, GEN11_GTPM));
	else
		WARN_ON_ONCE(I915_READ(gen6_pm_iir(dev_priv)) & dev_priv->pm_rps_events);

	rps->interrupts_enabled = true;
	gen6_gt_pm_enable_irq(gt, dev_priv->pm_rps_events);

	spin_unlock_irq(&gt->irq_lock);
}