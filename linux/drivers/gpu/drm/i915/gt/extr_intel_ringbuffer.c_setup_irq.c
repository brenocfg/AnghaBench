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
struct intel_engine_cs {int /*<<< orphan*/  irq_disable; int /*<<< orphan*/  irq_enable; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen5_irq_disable ; 
 int /*<<< orphan*/  gen5_irq_enable ; 
 int /*<<< orphan*/  gen6_irq_disable ; 
 int /*<<< orphan*/  gen6_irq_enable ; 
 int /*<<< orphan*/  i8xx_irq_disable ; 
 int /*<<< orphan*/  i8xx_irq_enable ; 
 int /*<<< orphan*/  i9xx_irq_disable ; 
 int /*<<< orphan*/  i9xx_irq_enable ; 

__attribute__((used)) static void setup_irq(struct intel_engine_cs *engine)
{
	struct drm_i915_private *i915 = engine->i915;

	if (INTEL_GEN(i915) >= 6) {
		engine->irq_enable = gen6_irq_enable;
		engine->irq_disable = gen6_irq_disable;
	} else if (INTEL_GEN(i915) >= 5) {
		engine->irq_enable = gen5_irq_enable;
		engine->irq_disable = gen5_irq_disable;
	} else if (INTEL_GEN(i915) >= 3) {
		engine->irq_enable = i9xx_irq_enable;
		engine->irq_disable = i9xx_irq_disable;
	} else {
		engine->irq_enable = i8xx_irq_enable;
		engine->irq_disable = i8xx_irq_disable;
	}
}