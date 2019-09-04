#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_MASTER_IRQ ; 
 int /*<<< orphan*/  GEN8_MASTER_IRQ_CONTROL ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_de_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen8_gt_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ibx_irq_postinstall (struct drm_device*) ; 
 int /*<<< orphan*/  ibx_irq_pre_postinstall (struct drm_device*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int gen8_irq_postinstall(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);

	if (HAS_PCH_SPLIT(dev_priv))
		ibx_irq_pre_postinstall(dev);

	gen8_gt_irq_postinstall(dev_priv);
	gen8_de_irq_postinstall(dev_priv);

	if (HAS_PCH_SPLIT(dev_priv))
		ibx_irq_postinstall(dev);

	I915_WRITE(GEN8_MASTER_IRQ, GEN8_MASTER_IRQ_CONTROL);
	POSTING_READ(GEN8_MASTER_IRQ);

	return 0;
}