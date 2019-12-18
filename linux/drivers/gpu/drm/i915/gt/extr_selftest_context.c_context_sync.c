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
struct TYPE_2__ {int /*<<< orphan*/  request; } ;
struct intel_timeline {int /*<<< orphan*/  mutex; TYPE_1__ last_request; } ;
struct intel_context {struct intel_timeline* timeline; } ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 struct i915_request* i915_request_get_rcu (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_retire_upto (struct i915_request*) ; 
 long i915_request_wait (struct i915_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i915_request* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int context_sync(struct intel_context *ce)
{
	struct intel_timeline *tl = ce->timeline;
	int err = 0;

	mutex_lock(&tl->mutex);
	do {
		struct i915_request *rq;
		long timeout;

		rcu_read_lock();
		rq = rcu_dereference(tl->last_request.request);
		if (rq)
			rq = i915_request_get_rcu(rq);
		rcu_read_unlock();
		if (!rq)
			break;

		timeout = i915_request_wait(rq, 0, HZ / 10);
		if (timeout < 0)
			err = timeout;
		else
			i915_request_retire_upto(rq);

		i915_request_put(rq);
	} while (!err);
	mutex_unlock(&tl->mutex);

	return err;
}