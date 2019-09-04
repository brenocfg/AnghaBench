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
struct cfq_rb_root {int dummy; } ;
struct cfq_group {int /*<<< orphan*/  rb_node; scalar_t__ weight; int /*<<< orphan*/  children_weight; int /*<<< orphan*/  nr_active; scalar_t__ vfraction; scalar_t__ leaf_weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_rb_erase (int /*<<< orphan*/ *,struct cfq_rb_root*) ; 
 struct cfq_group* cfqg_parent (struct cfq_group*) ; 

__attribute__((used)) static void
cfq_group_service_tree_del(struct cfq_rb_root *st, struct cfq_group *cfqg)
{
	struct cfq_group *pos = cfqg;
	bool propagate;

	/*
	 * Undo activation from cfq_group_service_tree_add().  Deactivate
	 * @cfqg and propagate deactivation upwards.
	 */
	propagate = !--pos->nr_active;
	pos->children_weight -= pos->leaf_weight;

	while (propagate) {
		struct cfq_group *parent = cfqg_parent(pos);

		/* @pos has 0 nr_active at this point */
		WARN_ON_ONCE(pos->children_weight);
		pos->vfraction = 0;

		if (!parent)
			break;

		propagate = !--parent->nr_active;
		parent->children_weight -= pos->weight;
		pos = parent;
	}

	/* remove from the service tree */
	if (!RB_EMPTY_NODE(&cfqg->rb_node))
		cfq_rb_erase(&cfqg->rb_node, st);
}