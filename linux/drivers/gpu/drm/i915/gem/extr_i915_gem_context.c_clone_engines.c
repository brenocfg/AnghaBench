#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_engine_cs {int dummy; } ;
struct i915_gem_engines {unsigned long num_engines; TYPE_1__** engines; int /*<<< orphan*/  rcu; } ;
struct i915_gem_context {int /*<<< orphan*/  engines; } ;
struct TYPE_4__ {struct intel_engine_cs* engine; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (TYPE_1__*) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct i915_gem_engines*) ; 
 int /*<<< orphan*/  __free_engines (struct i915_gem_engines*,unsigned long) ; 
 int /*<<< orphan*/  engines ; 
 int /*<<< orphan*/  free_engines (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_clear_user_engines (struct i915_gem_context*) ; 
 struct i915_gem_engines* i915_gem_context_lock_engines (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_set_user_engines (struct i915_gem_context*) ; 
 int /*<<< orphan*/  i915_gem_context_unlock_engines (struct i915_gem_context*) ; 
 int i915_gem_context_user_engines (struct i915_gem_context*) ; 
 int /*<<< orphan*/  init_rcu_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* intel_context_create (struct i915_gem_context*,struct intel_engine_cs*) ; 
 scalar_t__ intel_engine_is_virtual (struct intel_engine_cs*) ; 
 TYPE_1__* intel_execlists_clone_virtual (struct i915_gem_context*,struct intel_engine_cs*) ; 
 struct i915_gem_engines* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct i915_gem_engines*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int clone_engines(struct i915_gem_context *dst,
			 struct i915_gem_context *src)
{
	struct i915_gem_engines *e = i915_gem_context_lock_engines(src);
	struct i915_gem_engines *clone;
	bool user_engines;
	unsigned long n;

	clone = kmalloc(struct_size(e, engines, e->num_engines), GFP_KERNEL);
	if (!clone)
		goto err_unlock;

	init_rcu_head(&clone->rcu);
	for (n = 0; n < e->num_engines; n++) {
		struct intel_engine_cs *engine;

		if (!e->engines[n]) {
			clone->engines[n] = NULL;
			continue;
		}
		engine = e->engines[n]->engine;

		/*
		 * Virtual engines are singletons; they can only exist
		 * inside a single context, because they embed their
		 * HW context... As each virtual context implies a single
		 * timeline (each engine can only dequeue a single request
		 * at any time), it would be surprising for two contexts
		 * to use the same engine. So let's create a copy of
		 * the virtual engine instead.
		 */
		if (intel_engine_is_virtual(engine))
			clone->engines[n] =
				intel_execlists_clone_virtual(dst, engine);
		else
			clone->engines[n] = intel_context_create(dst, engine);
		if (IS_ERR_OR_NULL(clone->engines[n])) {
			__free_engines(clone, n);
			goto err_unlock;
		}
	}
	clone->num_engines = n;

	user_engines = i915_gem_context_user_engines(src);
	i915_gem_context_unlock_engines(src);

	free_engines(dst->engines);
	RCU_INIT_POINTER(dst->engines, clone);
	if (user_engines)
		i915_gem_context_set_user_engines(dst);
	else
		i915_gem_context_clear_user_engines(dst);
	return 0;

err_unlock:
	i915_gem_context_unlock_engines(src);
	return -ENOMEM;
}