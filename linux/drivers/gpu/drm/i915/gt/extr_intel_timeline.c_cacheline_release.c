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
struct intel_timeline_cacheline {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_active_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cacheline_release(struct intel_timeline_cacheline *cl)
{
	if (cl)
		i915_active_release(&cl->active);
}