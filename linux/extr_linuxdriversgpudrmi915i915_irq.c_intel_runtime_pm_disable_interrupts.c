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
struct TYPE_6__ {int /*<<< orphan*/  irq; TYPE_1__* driver; } ;
struct TYPE_5__ {int irqs_enabled; } ;
struct drm_i915_private {TYPE_3__ drm; TYPE_2__ runtime_pm; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* irq_uninstall ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

void intel_runtime_pm_disable_interrupts(struct drm_i915_private *dev_priv)
{
	dev_priv->drm.driver->irq_uninstall(&dev_priv->drm);
	dev_priv->runtime_pm.irqs_enabled = false;
	synchronize_irq(dev_priv->drm.irq);
}