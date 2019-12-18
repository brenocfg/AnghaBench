#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  queue_priority_hint; } ;
struct TYPE_10__ {scalar_t__ submit_request; TYPE_4__ active; TYPE_3__ execlists; int /*<<< orphan*/  name; } ;
struct virtual_engine {TYPE_5__ base; struct i915_request* request; } ;
struct TYPE_7__ {int /*<<< orphan*/  link; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {TYPE_2__ sched; TYPE_1__ fence; int /*<<< orphan*/  engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  __i915_request_submit (struct i915_request*) ; 
 scalar_t__ i915_request_completed (struct i915_request*) ; 
 struct i915_request* i915_request_get (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_prio (struct i915_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct virtual_engine* to_virtual_engine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtual_queue (struct virtual_engine*) ; 

__attribute__((used)) static void virtual_submit_request(struct i915_request *rq)
{
	struct virtual_engine *ve = to_virtual_engine(rq->engine);
	struct i915_request *old;
	unsigned long flags;

	GEM_TRACE("%s: rq=%llx:%lld\n",
		  ve->base.name,
		  rq->fence.context,
		  rq->fence.seqno);

	GEM_BUG_ON(ve->base.submit_request != virtual_submit_request);

	spin_lock_irqsave(&ve->base.active.lock, flags);

	old = ve->request;
	if (old) { /* background completion event from preempt-to-busy */
		GEM_BUG_ON(!i915_request_completed(old));
		__i915_request_submit(old);
		i915_request_put(old);
	}

	if (i915_request_completed(rq)) {
		__i915_request_submit(rq);

		ve->base.execlists.queue_priority_hint = INT_MIN;
		ve->request = NULL;
	} else {
		ve->base.execlists.queue_priority_hint = rq_prio(rq);
		ve->request = i915_request_get(rq);

		GEM_BUG_ON(!list_empty(virtual_queue(ve)));
		list_move_tail(&rq->sched.link, virtual_queue(ve));

		tasklet_schedule(&ve->base.execlists.tasklet);
	}

	spin_unlock_irqrestore(&ve->base.active.lock, flags);
}