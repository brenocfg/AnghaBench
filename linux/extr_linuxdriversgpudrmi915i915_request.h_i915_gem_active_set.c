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
struct i915_request {int /*<<< orphan*/  active_list; } ;
struct i915_gem_active {int /*<<< orphan*/  request; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct i915_request*) ; 

__attribute__((used)) static inline void
i915_gem_active_set(struct i915_gem_active *active,
		    struct i915_request *request)
{
	list_move(&active->link, &request->active_list);
	rcu_assign_pointer(active->request, request);
}