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
struct intel_engine_cs {int /*<<< orphan*/  i915; int /*<<< orphan*/  sseu; int /*<<< orphan*/  pool; int /*<<< orphan*/  barrier_tasks; } ;
struct TYPE_2__ {int /*<<< orphan*/  sseu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_PHYSICAL ; 
 TYPE_1__* RUNTIME_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int init_status_page (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init__pm (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_active (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_init_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_cmd_parser (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_ctx_wa (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_execlists (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_hangcheck (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_whitelist (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_init_workarounds (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_engine_pool_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_sseu_from_device_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_engine_setup_common(struct intel_engine_cs *engine)
{
	int err;

	init_llist_head(&engine->barrier_tasks);

	err = init_status_page(engine);
	if (err)
		return err;

	intel_engine_init_active(engine, ENGINE_PHYSICAL);
	intel_engine_init_breadcrumbs(engine);
	intel_engine_init_execlists(engine);
	intel_engine_init_hangcheck(engine);
	intel_engine_init_cmd_parser(engine);
	intel_engine_init__pm(engine);

	intel_engine_pool_init(&engine->pool);

	/* Use the whole device by default */
	engine->sseu =
		intel_sseu_from_device_info(&RUNTIME_INFO(engine->i915)->sseu);

	intel_engine_init_workarounds(engine);
	intel_engine_init_whitelist(engine);
	intel_engine_init_ctx_wa(engine);

	return 0;
}