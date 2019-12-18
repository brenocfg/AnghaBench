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
struct intel_engine_cs {int /*<<< orphan*/  emit_fini_breadcrumb; int /*<<< orphan*/  irq_disable; int /*<<< orphan*/  irq_enable; int /*<<< orphan*/  irq_enable_mask; int /*<<< orphan*/  emit_flush; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PM_VEBOX_USER_INTERRUPT ; 
 int /*<<< orphan*/  gen6_ring_flush ; 
 int /*<<< orphan*/  gen7_xcs_emit_breadcrumb ; 
 int /*<<< orphan*/  hsw_vebox_irq_disable ; 
 int /*<<< orphan*/  hsw_vebox_irq_enable ; 

__attribute__((used)) static void setup_vecs(struct intel_engine_cs *engine)
{
	struct drm_i915_private *i915 = engine->i915;

	GEM_BUG_ON(INTEL_GEN(i915) < 7);

	engine->emit_flush = gen6_ring_flush;
	engine->irq_enable_mask = PM_VEBOX_USER_INTERRUPT;
	engine->irq_enable = hsw_vebox_irq_enable;
	engine->irq_disable = hsw_vebox_irq_disable;

	engine->emit_fini_breadcrumb = gen7_xcs_emit_breadcrumb;
}