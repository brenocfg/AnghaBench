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
struct intel_rps {int interrupts_enabled; int /*<<< orphan*/  work; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {struct intel_rps rps; } ;
struct drm_i915_private {TYPE_1__ drm; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  pm_rps_events; TYPE_2__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_PMINTRMSK ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  READ_ONCE (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen11_reset_rps_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_disable_pm_irq (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen6_reset_rps_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_sanitize_rps_pm_mask (struct drm_i915_private*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

void gen6_disable_rps_interrupts(struct drm_i915_private *dev_priv)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;

	if (!READ_ONCE(rps->interrupts_enabled))
		return;

	spin_lock_irq(&dev_priv->irq_lock);
	rps->interrupts_enabled = false;

	I915_WRITE(GEN6_PMINTRMSK, gen6_sanitize_rps_pm_mask(dev_priv, ~0u));

	gen6_disable_pm_irq(dev_priv, dev_priv->pm_rps_events);

	spin_unlock_irq(&dev_priv->irq_lock);
	synchronize_irq(dev_priv->drm.irq);

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