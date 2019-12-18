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
struct sched_cache {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_1__ active; } ;
struct i915_sched_node {int dummy; } ;
struct i915_request {int /*<<< orphan*/  engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 struct intel_engine_cs* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sched_cache*,int /*<<< orphan*/ ,int) ; 
 struct i915_request* node_to_request (struct i915_sched_node const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct intel_engine_cs *
sched_lock_engine(const struct i915_sched_node *node,
		  struct intel_engine_cs *locked,
		  struct sched_cache *cache)
{
	const struct i915_request *rq = node_to_request(node);
	struct intel_engine_cs *engine;

	GEM_BUG_ON(!locked);

	/*
	 * Virtual engines complicate acquiring the engine timeline lock,
	 * as their rq->engine pointer is not stable until under that
	 * engine lock. The simple ploy we use is to take the lock then
	 * check that the rq still belongs to the newly locked engine.
	 */
	while (locked != (engine = READ_ONCE(rq->engine))) {
		spin_unlock(&locked->active.lock);
		memset(cache, 0, sizeof(*cache));
		spin_lock(&engine->active.lock);
		locked = engine;
	}

	GEM_BUG_ON(locked != engine);
	return locked;
}