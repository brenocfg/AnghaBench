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
struct TYPE_3__ {scalar_t__ pm_iir; } ;
struct TYPE_4__ {TYPE_1__ rps; } ;
struct drm_i915_private {int /*<<< orphan*/  irq_lock; TYPE_2__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_GTPM ; 
 scalar_t__ gen11_reset_one_iir (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gen11_reset_rps_interrupts(struct drm_i915_private *dev_priv)
{
	spin_lock_irq(&dev_priv->irq_lock);

	while (gen11_reset_one_iir(dev_priv, 0, GEN11_GTPM))
		;

	dev_priv->gt_pm.rps.pm_iir = 0;

	spin_unlock_irq(&dev_priv->irq_lock);
}