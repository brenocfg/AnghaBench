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
struct intel_engine_cs {int emit_fini_breadcrumb_dw; struct intel_context* kernel_context; int /*<<< orphan*/  (* set_default_submission ) (struct intel_engine_cs*) ;} ;
struct intel_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct intel_context*) ; 
 int PTR_ERR (struct intel_context*) ; 
 struct intel_context* create_kernel_context (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_context_put (struct intel_context*) ; 
 int /*<<< orphan*/  intel_context_unpin (struct intel_context*) ; 
 int measure_breadcrumb_dw (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*) ; 

int intel_engine_init_common(struct intel_engine_cs *engine)
{
	struct intel_context *ce;
	int ret;

	engine->set_default_submission(engine);

	/*
	 * We may need to do things with the shrinker which
	 * require us to immediately switch back to the default
	 * context. This can cause a problem as pinning the
	 * default context also requires GTT space which may not
	 * be available. To avoid this we always pin the default
	 * context.
	 */
	ce = create_kernel_context(engine);
	if (IS_ERR(ce))
		return PTR_ERR(ce);

	engine->kernel_context = ce;

	ret = measure_breadcrumb_dw(engine);
	if (ret < 0)
		goto err_unpin;

	engine->emit_fini_breadcrumb_dw = ret;

	return 0;

err_unpin:
	intel_context_unpin(ce);
	intel_context_put(ce);
	return ret;
}