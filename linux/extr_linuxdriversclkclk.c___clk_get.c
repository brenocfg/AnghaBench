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
struct clk_core {int /*<<< orphan*/  ref; int /*<<< orphan*/  owner; } ;
struct clk {struct clk_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int __clk_get(struct clk *clk)
{
	struct clk_core *core = !clk ? NULL : clk->core;

	if (core) {
		if (!try_module_get(core->owner))
			return 0;

		kref_get(&core->ref);
	}
	return 1;
}