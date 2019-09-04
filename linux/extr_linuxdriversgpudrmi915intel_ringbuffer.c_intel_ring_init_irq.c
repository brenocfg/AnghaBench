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
struct intel_engine_cs {int /*<<< orphan*/  irq_disable; int /*<<< orphan*/  irq_enable; int /*<<< orphan*/  irq_seqno_barrier; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen5_irq_disable ; 
 int /*<<< orphan*/  gen5_irq_enable ; 
 int /*<<< orphan*/  gen5_seqno_barrier ; 
 int /*<<< orphan*/  gen6_irq_disable ; 
 int /*<<< orphan*/  gen6_irq_enable ; 
 int /*<<< orphan*/  gen6_seqno_barrier ; 
 int /*<<< orphan*/  i8xx_irq_disable ; 
 int /*<<< orphan*/  i8xx_irq_enable ; 
 int /*<<< orphan*/  i9xx_irq_disable ; 
 int /*<<< orphan*/  i9xx_irq_enable ; 

__attribute__((used)) static void intel_ring_init_irq(struct drm_i915_private *dev_priv,
				struct intel_engine_cs *engine)
{
	if (INTEL_GEN(dev_priv) >= 6) {
		engine->irq_enable = gen6_irq_enable;
		engine->irq_disable = gen6_irq_disable;
		engine->irq_seqno_barrier = gen6_seqno_barrier;
	} else if (INTEL_GEN(dev_priv) >= 5) {
		engine->irq_enable = gen5_irq_enable;
		engine->irq_disable = gen5_irq_disable;
		engine->irq_seqno_barrier = gen5_seqno_barrier;
	} else if (INTEL_GEN(dev_priv) >= 3) {
		engine->irq_enable = i9xx_irq_enable;
		engine->irq_disable = i9xx_irq_disable;
	} else {
		engine->irq_enable = i8xx_irq_enable;
		engine->irq_disable = i8xx_irq_disable;
	}
}