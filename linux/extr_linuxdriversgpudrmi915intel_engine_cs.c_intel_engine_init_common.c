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
struct intel_engine_cs {int /*<<< orphan*/  (* set_default_submission ) (struct intel_engine_cs*) ;struct drm_i915_private* i915; } ;
struct intel_context {int dummy; } ;
struct drm_i915_private {scalar_t__ kernel_context; scalar_t__ preempt_context; } ;

/* Variables and functions */
 scalar_t__ HWS_NEEDS_PHYSICAL (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct intel_context*) ; 
 int PTR_ERR (struct intel_context*) ; 
 int /*<<< orphan*/  __intel_context_unpin (scalar_t__,struct intel_engine_cs*) ; 
 int init_phys_status_page (struct intel_engine_cs*) ; 
 int init_status_page (struct intel_engine_cs*) ; 
 struct intel_context* intel_context_pin (scalar_t__,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_fini_breadcrumbs (struct intel_engine_cs*) ; 
 int intel_engine_init_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*) ; 

int intel_engine_init_common(struct intel_engine_cs *engine)
{
	struct drm_i915_private *i915 = engine->i915;
	struct intel_context *ce;
	int ret;

	engine->set_default_submission(engine);

	/* We may need to do things with the shrinker which
	 * require us to immediately switch back to the default
	 * context. This can cause a problem as pinning the
	 * default context also requires GTT space which may not
	 * be available. To avoid this we always pin the default
	 * context.
	 */
	ce = intel_context_pin(i915->kernel_context, engine);
	if (IS_ERR(ce))
		return PTR_ERR(ce);

	/*
	 * Similarly the preempt context must always be available so that
	 * we can interrupt the engine at any time.
	 */
	if (i915->preempt_context) {
		ce = intel_context_pin(i915->preempt_context, engine);
		if (IS_ERR(ce)) {
			ret = PTR_ERR(ce);
			goto err_unpin_kernel;
		}
	}

	ret = intel_engine_init_breadcrumbs(engine);
	if (ret)
		goto err_unpin_preempt;

	if (HWS_NEEDS_PHYSICAL(i915))
		ret = init_phys_status_page(engine);
	else
		ret = init_status_page(engine);
	if (ret)
		goto err_breadcrumbs;

	return 0;

err_breadcrumbs:
	intel_engine_fini_breadcrumbs(engine);
err_unpin_preempt:
	if (i915->preempt_context)
		__intel_context_unpin(i915->preempt_context, engine);

err_unpin_kernel:
	__intel_context_unpin(i915->kernel_context, engine);
	return ret;
}