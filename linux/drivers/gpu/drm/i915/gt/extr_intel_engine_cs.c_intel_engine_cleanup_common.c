#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  requests; } ;
struct intel_engine_cs {int /*<<< orphan*/  whitelist; int /*<<< orphan*/  wa_list; int /*<<< orphan*/  ctx_wa_list; int /*<<< orphan*/  barrier_tasks; int /*<<< orphan*/  kernel_context; scalar_t__ default_state; int /*<<< orphan*/  pool; TYPE_1__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  cleanup_status_page (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  i915_gem_object_put (scalar_t__) ; 
 int /*<<< orphan*/  intel_context_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_context_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_cleanup_cmd_parser (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_fini_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_pool_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_wa_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llist_empty (int /*<<< orphan*/ *) ; 

void intel_engine_cleanup_common(struct intel_engine_cs *engine)
{
	GEM_BUG_ON(!list_empty(&engine->active.requests));

	cleanup_status_page(engine);

	intel_engine_pool_fini(&engine->pool);
	intel_engine_fini_breadcrumbs(engine);
	intel_engine_cleanup_cmd_parser(engine);

	if (engine->default_state)
		i915_gem_object_put(engine->default_state);

	intel_context_unpin(engine->kernel_context);
	intel_context_put(engine->kernel_context);
	GEM_BUG_ON(!llist_empty(&engine->barrier_tasks));

	intel_wa_list_free(&engine->ctx_wa_list);
	intel_wa_list_free(&engine->wa_list);
	intel_wa_list_free(&engine->whitelist);
}