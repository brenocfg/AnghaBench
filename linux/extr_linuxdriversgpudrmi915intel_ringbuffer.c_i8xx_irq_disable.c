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
struct intel_engine_cs {int /*<<< orphan*/  irq_enable_mask; struct drm_i915_private* i915; } ;
struct drm_i915_private {int /*<<< orphan*/  irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMR ; 

__attribute__((used)) static void
i8xx_irq_disable(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	dev_priv->irq_mask |= engine->irq_enable_mask;
	I915_WRITE16(IMR, dev_priv->irq_mask);
}