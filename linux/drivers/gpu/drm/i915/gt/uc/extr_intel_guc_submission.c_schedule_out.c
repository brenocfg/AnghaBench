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
struct i915_request {TYPE_1__* engine; } ;
struct TYPE_2__ {int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 int /*<<< orphan*/  intel_gt_pm_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_i915_request_out (struct i915_request*) ; 

__attribute__((used)) static void schedule_out(struct i915_request *rq)
{
	trace_i915_request_out(rq);

	intel_gt_pm_put(rq->engine->gt);
	i915_request_put(rq);
}