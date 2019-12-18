#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  rb_root; } ;
struct TYPE_6__ {TYPE_1__ queue; } ;
struct intel_engine_cs {TYPE_3__ active; TYPE_2__ execlists; } ;
struct TYPE_8__ {int /*<<< orphan*/  link; } ;
struct i915_request {TYPE_4__ sched; struct intel_engine_cs* engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_request (struct intel_engine_cs*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_prio (struct i915_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  submit_queue (struct intel_engine_cs*,struct i915_request*) ; 

__attribute__((used)) static void execlists_submit_request(struct i915_request *request)
{
	struct intel_engine_cs *engine = request->engine;
	unsigned long flags;

	/* Will be called from irq-context when using foreign fences. */
	spin_lock_irqsave(&engine->active.lock, flags);

	queue_request(engine, &request->sched, rq_prio(request));

	GEM_BUG_ON(RB_EMPTY_ROOT(&engine->execlists.queue.rb_root));
	GEM_BUG_ON(list_empty(&request->sched.link));

	submit_queue(engine, request);

	spin_unlock_irqrestore(&engine->active.lock, flags);
}