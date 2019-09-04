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
struct clk_core {int /*<<< orphan*/  name; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; struct clk_core* parent; } ;
struct clk {struct clk_core* core; } ;

/* Variables and functions */
 scalar_t__ match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool clk_has_parent(struct clk *clk, struct clk *parent)
{
	struct clk_core *core, *parent_core;

	/* NULL clocks should be nops, so return success if either is NULL. */
	if (!clk || !parent)
		return true;

	core = clk->core;
	parent_core = parent->core;

	/* Optimize for the case where the parent is already the parent. */
	if (core->parent == parent_core)
		return true;

	return match_string(core->parent_names, core->num_parents,
			    parent_core->name) >= 0;
}