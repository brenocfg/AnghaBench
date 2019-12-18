#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct i915_gem_engines {unsigned int num_engines; int /*<<< orphan*/ ** engines; int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct i915_gem_engines* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  engines ; 
 int /*<<< orphan*/  init_rcu_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_context_get (int /*<<< orphan*/ *) ; 
 struct i915_gem_engines* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct i915_gem_engines*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct i915_gem_engines *
__copy_engines(struct i915_gem_engines *e)
{
	struct i915_gem_engines *copy;
	unsigned int n;

	copy = kmalloc(struct_size(e, engines, e->num_engines), GFP_KERNEL);
	if (!copy)
		return ERR_PTR(-ENOMEM);

	init_rcu_head(&copy->rcu);
	for (n = 0; n < e->num_engines; n++) {
		if (e->engines[n])
			copy->engines[n] = intel_context_get(e->engines[n]);
		else
			copy->engines[n] = NULL;
	}
	copy->num_engines = n;

	return copy;
}