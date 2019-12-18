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
struct i915_request {TYPE_1__* timeline; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  i915_request_add (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_get (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_retire_upto (struct i915_request*) ; 
 long i915_request_wait (struct i915_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int request_sync(struct i915_request *rq)
{
	long timeout;
	int err = 0;

	i915_request_get(rq);

	i915_request_add(rq);
	timeout = i915_request_wait(rq, 0, HZ / 10);
	if (timeout < 0) {
		err = timeout;
	} else {
		mutex_lock(&rq->timeline->mutex);
		i915_request_retire_upto(rq);
		mutex_unlock(&rq->timeline->mutex);
	}

	i915_request_put(rq);

	return err;
}