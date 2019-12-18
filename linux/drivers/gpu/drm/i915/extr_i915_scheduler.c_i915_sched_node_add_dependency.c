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
struct i915_sched_node {int dummy; } ;
struct i915_dependency {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int I915_DEPENDENCY_ALLOC ; 
 int I915_DEPENDENCY_EXTERNAL ; 
 int /*<<< orphan*/  __i915_sched_node_add_dependency (struct i915_sched_node*,struct i915_sched_node*,struct i915_dependency*,int) ; 
 struct i915_dependency* i915_dependency_alloc () ; 
 int /*<<< orphan*/  i915_dependency_free (struct i915_dependency*) ; 

int i915_sched_node_add_dependency(struct i915_sched_node *node,
				   struct i915_sched_node *signal)
{
	struct i915_dependency *dep;

	dep = i915_dependency_alloc();
	if (!dep)
		return -ENOMEM;

	if (!__i915_sched_node_add_dependency(node, signal, dep,
					      I915_DEPENDENCY_EXTERNAL |
					      I915_DEPENDENCY_ALLOC))
		i915_dependency_free(dep);

	return 0;
}