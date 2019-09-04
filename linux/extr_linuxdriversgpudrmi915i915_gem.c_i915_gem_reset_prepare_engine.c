#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct i915_request* (* prepare ) (struct intel_engine_cs*) ;} ;
struct intel_engine_cs {TYPE_1__ reset; int /*<<< orphan*/  i915; } ;
struct TYPE_4__ {int /*<<< orphan*/  error; } ;
struct i915_request {TYPE_2__ fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct i915_request* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i915_request* stub1 (struct intel_engine_cs*) ; 

struct i915_request *
i915_gem_reset_prepare_engine(struct intel_engine_cs *engine)
{
	struct i915_request *request;

	/*
	 * During the reset sequence, we must prevent the engine from
	 * entering RC6. As the context state is undefined until we restart
	 * the engine, if it does enter RC6 during the reset, the state
	 * written to the powercontext is undefined and so we may lose
	 * GPU state upon resume, i.e. fail to restart after a reset.
	 */
	intel_uncore_forcewake_get(engine->i915, FORCEWAKE_ALL);

	request = engine->reset.prepare(engine);
	if (request && request->fence.error == -EIO)
		request = ERR_PTR(-EIO); /* Previous reset failed! */

	return request;
}