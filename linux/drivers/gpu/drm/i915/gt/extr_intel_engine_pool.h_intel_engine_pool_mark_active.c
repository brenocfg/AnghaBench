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
struct intel_engine_pool_node {int /*<<< orphan*/  active; } ;
struct i915_request {int /*<<< orphan*/  timeline; } ;

/* Variables and functions */
 int i915_active_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i915_request*) ; 

__attribute__((used)) static inline int
intel_engine_pool_mark_active(struct intel_engine_pool_node *node,
			      struct i915_request *rq)
{
	return i915_active_ref(&node->active, rq->timeline, rq);
}