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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_2__ active; } ;
struct TYPE_3__ {int /*<<< orphan*/  link; } ;
struct i915_request {TYPE_1__ sched; int /*<<< orphan*/  engine; } ;

/* Variables and functions */
 struct intel_engine_cs* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void remove_from_engine(struct i915_request *rq)
{
	struct intel_engine_cs *engine, *locked;

	/*
	 * Virtual engines complicate acquiring the engine timeline lock,
	 * as their rq->engine pointer is not stable until under that
	 * engine lock. The simple ploy we use is to take the lock then
	 * check that the rq still belongs to the newly locked engine.
	 */
	locked = READ_ONCE(rq->engine);
	spin_lock(&locked->active.lock);
	while (unlikely(locked != (engine = READ_ONCE(rq->engine)))) {
		spin_unlock(&locked->active.lock);
		spin_lock(&engine->active.lock);
		locked = engine;
	}
	list_del(&rq->sched.link);
	spin_unlock(&locked->active.lock);
}