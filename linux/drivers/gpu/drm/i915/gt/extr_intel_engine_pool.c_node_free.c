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
struct intel_engine_pool_node {int /*<<< orphan*/  active; int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_active_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct intel_engine_pool_node*) ; 

__attribute__((used)) static void node_free(struct intel_engine_pool_node *node)
{
	i915_gem_object_put(node->obj);
	i915_active_fini(&node->active);
	kfree(node);
}