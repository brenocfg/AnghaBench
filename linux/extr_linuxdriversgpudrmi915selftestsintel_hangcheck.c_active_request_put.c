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
struct TYPE_4__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {int /*<<< orphan*/  i915; TYPE_2__ fence; TYPE_1__* engine; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_TRACE_DUMP () ; 
 int HZ ; 
 int /*<<< orphan*/  i915_gem_set_wedged (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_global_seqno (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 scalar_t__ i915_request_wait (struct i915_request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int active_request_put(struct i915_request *rq)
{
	int err = 0;

	if (!rq)
		return 0;

	if (i915_request_wait(rq, 0, 5 * HZ) < 0) {
		GEM_TRACE("%s timed out waiting for completion of fence %llx:%d, seqno %d.\n",
			  rq->engine->name,
			  rq->fence.context,
			  rq->fence.seqno,
			  i915_request_global_seqno(rq));
		GEM_TRACE_DUMP();

		i915_gem_set_wedged(rq->i915);
		err = -EIO;
	}

	i915_request_put(rq);

	return err;
}