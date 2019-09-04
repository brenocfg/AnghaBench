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
struct intel_engine_cs {int /*<<< orphan*/  irq_enable_mask; int /*<<< orphan*/  emit_flush; int /*<<< orphan*/  set_default_submission; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GT_BSD_USER_INTERRUPT ; 
 int /*<<< orphan*/  I915_BSD_USER_INTERRUPT ; 
 int /*<<< orphan*/  ILK_BSD_USER_INTERRUPT ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN5 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bsd_ring_flush ; 
 int /*<<< orphan*/  gen6_bsd_ring_flush ; 
 int /*<<< orphan*/  gen6_bsd_set_default_submission ; 
 int intel_init_ring_buffer (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_ring_default_vfuncs (struct drm_i915_private*,struct intel_engine_cs*) ; 

int intel_init_bsd_ring_buffer(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;

	intel_ring_default_vfuncs(dev_priv, engine);

	if (INTEL_GEN(dev_priv) >= 6) {
		/* gen6 bsd needs a special wa for tail updates */
		if (IS_GEN6(dev_priv))
			engine->set_default_submission = gen6_bsd_set_default_submission;
		engine->emit_flush = gen6_bsd_ring_flush;
		engine->irq_enable_mask = GT_BSD_USER_INTERRUPT;
	} else {
		engine->emit_flush = bsd_ring_flush;
		if (IS_GEN5(dev_priv))
			engine->irq_enable_mask = ILK_BSD_USER_INTERRUPT;
		else
			engine->irq_enable_mask = I915_BSD_USER_INTERRUPT;
	}

	return intel_init_ring_buffer(engine);
}