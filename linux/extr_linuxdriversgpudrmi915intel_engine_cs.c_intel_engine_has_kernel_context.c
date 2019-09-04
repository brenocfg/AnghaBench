#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  last_request; } ;
struct intel_engine_cs {struct intel_context const* last_retired_context; TYPE_3__ timeline; TYPE_2__* i915; } ;
struct intel_context {int dummy; } ;
struct i915_request {struct intel_context const* hw_context; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_5__ {TYPE_1__ drm; int /*<<< orphan*/  kernel_context; } ;

/* Variables and functions */
 struct i915_request* __i915_gem_active_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct intel_context* to_intel_context (int /*<<< orphan*/ ,struct intel_engine_cs const*) ; 

bool intel_engine_has_kernel_context(const struct intel_engine_cs *engine)
{
	const struct intel_context *kernel_context =
		to_intel_context(engine->i915->kernel_context, engine);
	struct i915_request *rq;

	lockdep_assert_held(&engine->i915->drm.struct_mutex);

	/*
	 * Check the last context seen by the engine. If active, it will be
	 * the last request that remains in the timeline. When idle, it is
	 * the last executed context as tracked by retirement.
	 */
	rq = __i915_gem_active_peek(&engine->timeline.last_request);
	if (rq)
		return rq->hw_context == kernel_context;
	else
		return engine->last_retired_context == kernel_context;
}