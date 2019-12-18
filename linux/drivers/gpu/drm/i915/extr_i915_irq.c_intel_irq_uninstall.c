#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int irqs_enabled; } ;
struct TYPE_5__ {int irq_enabled; TYPE_1__* pdev; } ;
struct drm_i915_private {TYPE_3__ runtime_pm; TYPE_2__ drm; } ;
struct TYPE_4__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_hpd_cancel_work (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_irq_reset (struct drm_i915_private*) ; 

void intel_irq_uninstall(struct drm_i915_private *dev_priv)
{
	int irq = dev_priv->drm.pdev->irq;

	/*
	 * FIXME we can get called twice during driver load
	 * error handling due to intel_modeset_cleanup()
	 * calling us out of sequence. Would be nice if
	 * it didn't do that...
	 */
	if (!dev_priv->drm.irq_enabled)
		return;

	dev_priv->drm.irq_enabled = false;

	intel_irq_reset(dev_priv);

	free_irq(irq, dev_priv);

	intel_hpd_cancel_work(dev_priv);
	dev_priv->runtime_pm.irqs_enabled = false;
}