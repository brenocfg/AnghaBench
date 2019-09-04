#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct TYPE_3__ {struct rb_node* rb_node; } ;
struct TYPE_4__ {TYPE_1__ rb_root; } ;
struct cfq_rb_root {TYPE_2__ rb; int /*<<< orphan*/ * rb_rightmost; } ;
struct cfq_group {int /*<<< orphan*/  rb_node; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ cfqg_key (struct cfq_rb_root*,struct cfq_group*) ; 
 struct cfq_group* rb_entry_cfqg (struct rb_node*) ; 
 int /*<<< orphan*/  rb_insert_color_cached (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 

__attribute__((used)) static void
__cfq_group_service_tree_add(struct cfq_rb_root *st, struct cfq_group *cfqg)
{
	struct rb_node **node = &st->rb.rb_root.rb_node;
	struct rb_node *parent = NULL;
	struct cfq_group *__cfqg;
	s64 key = cfqg_key(st, cfqg);
	bool leftmost = true, rightmost = true;

	while (*node != NULL) {
		parent = *node;
		__cfqg = rb_entry_cfqg(parent);

		if (key < cfqg_key(st, __cfqg)) {
			node = &parent->rb_left;
			rightmost = false;
		} else {
			node = &parent->rb_right;
			leftmost = false;
		}
	}

	if (rightmost)
		st->rb_rightmost = &cfqg->rb_node;

	rb_link_node(&cfqg->rb_node, parent, node);
	rb_insert_color_cached(&cfqg->rb_node, &st->rb, leftmost);
}