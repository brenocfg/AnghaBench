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
struct intel_engine_cs {struct intel_context* kernel_context; int /*<<< orphan*/  pool; } ;
struct intel_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_MOCK ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct intel_context*) ; 
 struct intel_context* create_kernel_context (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_fini_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init__pm (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_active (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_init_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_execlists (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_pool_init (int /*<<< orphan*/ *) ; 

int mock_engine_init(struct intel_engine_cs *engine)
{
	struct intel_context *ce;

	intel_engine_init_active(engine, ENGINE_MOCK);
	intel_engine_init_breadcrumbs(engine);
	intel_engine_init_execlists(engine);
	intel_engine_init__pm(engine);
	intel_engine_pool_init(&engine->pool);

	ce = create_kernel_context(engine);
	if (IS_ERR(ce))
		goto err_breadcrumbs;

	engine->kernel_context = ce;
	return 0;

err_breadcrumbs:
	intel_engine_fini_breadcrumbs(engine);
	return -ENOMEM;
}