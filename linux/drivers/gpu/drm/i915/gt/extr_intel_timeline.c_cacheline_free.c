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
struct intel_timeline_cacheline {int /*<<< orphan*/  active; int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE_FREE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __idle_cacheline_free (struct intel_timeline_cacheline*) ; 
 scalar_t__ i915_active_is_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptr_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cacheline_free(struct intel_timeline_cacheline *cl)
{
	GEM_BUG_ON(ptr_test_bit(cl->vaddr, CACHELINE_FREE));
	cl->vaddr = ptr_set_bit(cl->vaddr, CACHELINE_FREE);

	if (i915_active_is_idle(&cl->active))
		__idle_cacheline_free(cl);
}