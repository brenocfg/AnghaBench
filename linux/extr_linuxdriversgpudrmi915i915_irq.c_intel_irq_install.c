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
struct TYPE_6__ {TYPE_2__* pdev; } ;
struct TYPE_4__ {int irqs_enabled; } ;
struct drm_i915_private {TYPE_3__ drm; TYPE_1__ runtime_pm; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int drm_irq_install (TYPE_3__*,int /*<<< orphan*/ ) ; 

int intel_irq_install(struct drm_i915_private *dev_priv)
{
	/*
	 * We enable some interrupt sources in our postinstall hooks, so mark
	 * interrupts as enabled _before_ actually enabling them to avoid
	 * special cases in our ordering checks.
	 */
	dev_priv->runtime_pm.irqs_enabled = true;

	return drm_irq_install(&dev_priv->drm, dev_priv->drm.pdev->irq);
}