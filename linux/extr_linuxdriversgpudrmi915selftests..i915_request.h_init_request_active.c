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
struct i915_gem_active {int /*<<< orphan*/  retire; int /*<<< orphan*/  link; int /*<<< orphan*/  request; } ;
typedef  scalar_t__ i915_gem_retire_fn ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_retire_noop ; 

__attribute__((used)) static inline void
init_request_active(struct i915_gem_active *active,
		    i915_gem_retire_fn retire)
{
	RCU_INIT_POINTER(active->request, NULL);
	INIT_LIST_HEAD(&active->link);
	active->retire = retire ?: i915_gem_retire_noop;
}