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
struct intel_rps {int interrupts_enabled; int /*<<< orphan*/  work; } ;
struct intel_gt {int /*<<< orphan*/  irq_lock; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {struct intel_gt gt; TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_PMINTRMSK ; 
 int /*<<< orphan*/  GEN6_PM_RPS_EVENTS ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  READ_ONCE (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen11_reset_rps_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_gt_pm_disable_irq (struct intel_gt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen6_reset_rps_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_sanitize_rps_pm_mask (struct drm_i915_private*,unsigned int) ; 
 int /*<<< orphan*/  intel_synchronize_irq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gen6_disable_rps_interrupts(struct drm_i915_private *dev_priv)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	struct intel_gt *gt = &dev_priv->gt;

	if (!READ_ONCE(rps->interrupts_enabled))
		return;

	spin_lock_irq(&gt->irq_lock);
	rps->interrupts_enabled = false;

	I915_WRITE(GEN6_PMINTRMSK, gen6_sanitize_rps_pm_mask(dev_priv, ~0u));

	gen6_gt_pm_disable_irq(gt, GEN6_PM_RPS_EVENTS);

	spin_unlock_irq(&gt->irq_lock);
	intel_synchronize_irq(dev_priv);

	/* Now that we will not be generating any more work, flush any
	 * outstanding tasks. As we are called on the RPS idle path,
	 * we will reset the GPU to minimum frequencies, so the current
	 * state of the worker can be discarded.
	 */
	cancel_work_sync(&rps->work);
	if (INTEL_GEN(dev_priv) >= 11)
		gen11_reset_rps_interrupts(dev_priv);
	else
		gen6_reset_rps_interrupts(dev_priv);
}