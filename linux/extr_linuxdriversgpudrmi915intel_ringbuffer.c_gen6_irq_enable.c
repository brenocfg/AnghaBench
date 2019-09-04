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
struct intel_engine_cs {int irq_enable_mask; int irq_keep_mask; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE_IMR (struct intel_engine_cs*,int) ; 
 int /*<<< orphan*/  gen5_enable_gt_irq (struct drm_i915_private*,int) ; 

__attribute__((used)) static void
gen6_irq_enable(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	I915_WRITE_IMR(engine,
		       ~(engine->irq_enable_mask |
			 engine->irq_keep_mask));
	gen5_enable_gt_irq(dev_priv, engine->irq_enable_mask);
}