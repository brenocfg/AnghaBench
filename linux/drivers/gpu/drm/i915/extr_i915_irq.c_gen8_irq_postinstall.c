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
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;
struct drm_i915_private {TYPE_1__ uncore; int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen8_de_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen8_gt_irq_postinstall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen8_master_intr_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibx_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ibx_irq_pre_postinstall (struct drm_i915_private*) ; 

__attribute__((used)) static void gen8_irq_postinstall(struct drm_i915_private *dev_priv)
{
	if (HAS_PCH_SPLIT(dev_priv))
		ibx_irq_pre_postinstall(dev_priv);

	gen8_gt_irq_postinstall(&dev_priv->gt);
	gen8_de_irq_postinstall(dev_priv);

	if (HAS_PCH_SPLIT(dev_priv))
		ibx_irq_postinstall(dev_priv);

	gen8_master_intr_enable(dev_priv->uncore.regs);
}