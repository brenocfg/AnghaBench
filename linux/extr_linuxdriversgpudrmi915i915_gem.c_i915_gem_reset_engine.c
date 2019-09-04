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
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct intel_engine_cs*,struct i915_request*) ;} ;
struct intel_engine_cs {TYPE_1__ reset; int /*<<< orphan*/  irq_posted; } ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 struct i915_request* i915_gem_reset_request (struct intel_engine_cs*,struct i915_request*,int) ; 
 int /*<<< orphan*/  smp_store_mb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*,struct i915_request*) ; 

void i915_gem_reset_engine(struct intel_engine_cs *engine,
			   struct i915_request *request,
			   bool stalled)
{
	/*
	 * Make sure this write is visible before we re-enable the interrupt
	 * handlers on another CPU, as tasklet_enable() resolves to just
	 * a compiler barrier which is insufficient for our purpose here.
	 */
	smp_store_mb(engine->irq_posted, 0);

	if (request)
		request = i915_gem_reset_request(engine, request, stalled);

	/* Setup the CS to resume from the breadcrumb of the hung request */
	engine->reset.reset(engine, request);
}