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
struct intel_engine_cs {int /*<<< orphan*/  timeline; scalar_t__ default_state; int /*<<< orphan*/  batch_pool; struct drm_i915_private* i915; } ;
struct drm_i915_private {scalar_t__ kernel_context; scalar_t__ preempt_context; } ;

/* Variables and functions */
 scalar_t__ HWS_NEEDS_PHYSICAL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  __intel_context_unpin (scalar_t__,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  cleanup_phys_status_page (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  cleanup_status_page (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  i915_gem_batch_pool_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_put (scalar_t__) ; 
 int /*<<< orphan*/  i915_timeline_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_engine_cleanup_cmd_parser (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_cleanup_scratch (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_fini_breadcrumbs (struct intel_engine_cs*) ; 

void intel_engine_cleanup_common(struct intel_engine_cs *engine)
{
	struct drm_i915_private *i915 = engine->i915;

	intel_engine_cleanup_scratch(engine);

	if (HWS_NEEDS_PHYSICAL(engine->i915))
		cleanup_phys_status_page(engine);
	else
		cleanup_status_page(engine);

	intel_engine_fini_breadcrumbs(engine);
	intel_engine_cleanup_cmd_parser(engine);
	i915_gem_batch_pool_fini(&engine->batch_pool);

	if (engine->default_state)
		i915_gem_object_put(engine->default_state);

	if (i915->preempt_context)
		__intel_context_unpin(i915->preempt_context, engine);
	__intel_context_unpin(i915->kernel_context, engine);

	i915_timeline_fini(&engine->timeline);
}