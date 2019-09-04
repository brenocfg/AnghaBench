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
struct clk_core {int orphan; struct clk_core* parent; int /*<<< orphan*/  child_node; int /*<<< orphan*/  children; struct clk_core* new_child; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_core_update_orphan_status (struct clk_core*,int) ; 
 int /*<<< orphan*/  clk_orphan_list ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clk_reparent(struct clk_core *core, struct clk_core *new_parent)
{
	bool was_orphan = core->orphan;

	hlist_del(&core->child_node);

	if (new_parent) {
		bool becomes_orphan = new_parent->orphan;

		/* avoid duplicate POST_RATE_CHANGE notifications */
		if (new_parent->new_child == core)
			new_parent->new_child = NULL;

		hlist_add_head(&core->child_node, &new_parent->children);

		if (was_orphan != becomes_orphan)
			clk_core_update_orphan_status(core, becomes_orphan);
	} else {
		hlist_add_head(&core->child_node, &clk_orphan_list);
		if (!was_orphan)
			clk_core_update_orphan_status(core, true);
	}

	core->parent = new_parent;
}