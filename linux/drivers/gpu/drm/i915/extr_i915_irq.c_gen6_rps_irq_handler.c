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
typedef  int u32 ;
struct intel_rps {int pm_iir; int /*<<< orphan*/  work; scalar_t__ interrupts_enabled; } ;
struct intel_gt {int /*<<< orphan*/  irq_lock; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {int pm_rps_events; int /*<<< orphan*/ * engine; struct intel_gt gt; TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int PM_VEBOX_CS_ERROR_INTERRUPT ; 
 int PM_VEBOX_USER_INTERRUPT ; 
 size_t VECS0 ; 
 int /*<<< orphan*/  gen6_gt_pm_mask_irq (struct intel_gt*,int) ; 
 int /*<<< orphan*/  intel_engine_breadcrumbs_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void gen6_rps_irq_handler(struct drm_i915_private *dev_priv, u32 pm_iir)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	struct intel_gt *gt = &dev_priv->gt;

	if (pm_iir & dev_priv->pm_rps_events) {
		spin_lock(&gt->irq_lock);
		gen6_gt_pm_mask_irq(gt, pm_iir & dev_priv->pm_rps_events);
		if (rps->interrupts_enabled) {
			rps->pm_iir |= pm_iir & dev_priv->pm_rps_events;
			schedule_work(&rps->work);
		}
		spin_unlock(&gt->irq_lock);
	}

	if (INTEL_GEN(dev_priv) >= 8)
		return;

	if (pm_iir & PM_VEBOX_USER_INTERRUPT)
		intel_engine_breadcrumbs_irq(dev_priv->engine[VECS0]);

	if (pm_iir & PM_VEBOX_CS_ERROR_INTERRUPT)
		DRM_DEBUG("Command parser error, pm_iir 0x%08x\n", pm_iir);
}