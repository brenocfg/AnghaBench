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
struct TYPE_6__ {int irq_enabled; TYPE_1__* pdev; } ;
struct TYPE_5__ {int irqs_enabled; } ;
struct drm_i915_private {TYPE_3__ drm; TYPE_2__ runtime_pm; } ;
struct TYPE_4__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  intel_irq_handler (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_irq_reset (struct drm_i915_private*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_i915_private*) ; 

int intel_irq_install(struct drm_i915_private *dev_priv)
{
	int irq = dev_priv->drm.pdev->irq;
	int ret;

	/*
	 * We enable some interrupt sources in our postinstall hooks, so mark
	 * interrupts as enabled _before_ actually enabling them to avoid
	 * special cases in our ordering checks.
	 */
	dev_priv->runtime_pm.irqs_enabled = true;

	dev_priv->drm.irq_enabled = true;

	intel_irq_reset(dev_priv);

	ret = request_irq(irq, intel_irq_handler(dev_priv),
			  IRQF_SHARED, DRIVER_NAME, dev_priv);
	if (ret < 0) {
		dev_priv->drm.irq_enabled = false;
		return ret;
	}

	intel_irq_postinstall(dev_priv);

	return ret;
}