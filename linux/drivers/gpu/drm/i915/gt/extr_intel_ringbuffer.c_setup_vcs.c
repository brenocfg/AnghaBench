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
struct intel_engine_cs {int /*<<< orphan*/  irq_enable_mask; int /*<<< orphan*/  emit_flush; int /*<<< orphan*/  emit_fini_breadcrumb; int /*<<< orphan*/  set_default_submission; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GT_BSD_USER_INTERRUPT ; 
 int /*<<< orphan*/  I915_BSD_USER_INTERRUPT ; 
 int /*<<< orphan*/  ILK_BSD_USER_INTERRUPT ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  bsd_ring_flush ; 
 int /*<<< orphan*/  gen6_bsd_ring_flush ; 
 int /*<<< orphan*/  gen6_bsd_set_default_submission ; 
 int /*<<< orphan*/  gen6_xcs_emit_breadcrumb ; 
 int /*<<< orphan*/  gen7_xcs_emit_breadcrumb ; 

__attribute__((used)) static void setup_vcs(struct intel_engine_cs *engine)
{
	struct drm_i915_private *i915 = engine->i915;

	if (INTEL_GEN(i915) >= 6) {
		/* gen6 bsd needs a special wa for tail updates */
		if (IS_GEN(i915, 6))
			engine->set_default_submission = gen6_bsd_set_default_submission;
		engine->emit_flush = gen6_bsd_ring_flush;
		engine->irq_enable_mask = GT_BSD_USER_INTERRUPT;

		if (IS_GEN(i915, 6))
			engine->emit_fini_breadcrumb = gen6_xcs_emit_breadcrumb;
		else
			engine->emit_fini_breadcrumb = gen7_xcs_emit_breadcrumb;
	} else {
		engine->emit_flush = bsd_ring_flush;
		if (IS_GEN(i915, 5))
			engine->irq_enable_mask = ILK_BSD_USER_INTERRUPT;
		else
			engine->irq_enable_mask = I915_BSD_USER_INTERRUPT;
	}
}