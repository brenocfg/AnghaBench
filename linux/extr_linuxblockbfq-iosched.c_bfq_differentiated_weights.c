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
struct TYPE_4__ {TYPE_1__* rb_node; } ;
struct bfq_data {TYPE_2__ queue_weights_tree; } ;
struct TYPE_3__ {scalar_t__ rb_right; scalar_t__ rb_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (TYPE_2__*) ; 

__attribute__((used)) static bool bfq_differentiated_weights(struct bfq_data *bfqd)
{
	/*
	 * For weights to differ, at least one of the trees must contain
	 * at least two nodes.
	 */
	return (!RB_EMPTY_ROOT(&bfqd->queue_weights_tree) &&
		(bfqd->queue_weights_tree.rb_node->rb_left ||
		 bfqd->queue_weights_tree.rb_node->rb_right)
#ifdef CONFIG_BFQ_GROUP_IOSCHED
	       ) ||
	       (!RB_EMPTY_ROOT(&bfqd->group_weights_tree) &&
		(bfqd->group_weights_tree.rb_node->rb_left ||
		 bfqd->group_weights_tree.rb_node->rb_right)
#endif
	       );
}