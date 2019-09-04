#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rb_node {int dummy; } ;
struct bfq_queue {int /*<<< orphan*/ * pos_root; int /*<<< orphan*/  pos_node; int /*<<< orphan*/  next_rq; } ;
struct bfq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rq_pos_tree; } ;

/* Variables and functions */
 TYPE_1__* bfq_bfqq_to_bfqg (struct bfq_queue*) ; 
 scalar_t__ bfq_class_idle (struct bfq_queue*) ; 
 struct bfq_queue* bfq_rq_pos_tree_lookup (struct bfq_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rb_node**,struct rb_node***) ; 
 scalar_t__ bfq_too_late_for_merging (struct bfq_queue*) ; 
 int /*<<< orphan*/  blk_rq_pos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_insert_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 

void bfq_pos_tree_add_move(struct bfq_data *bfqd, struct bfq_queue *bfqq)
{
	struct rb_node **p, *parent;
	struct bfq_queue *__bfqq;

	if (bfqq->pos_root) {
		rb_erase(&bfqq->pos_node, bfqq->pos_root);
		bfqq->pos_root = NULL;
	}

	/*
	 * bfqq cannot be merged any longer (see comments in
	 * bfq_setup_cooperator): no point in adding bfqq into the
	 * position tree.
	 */
	if (bfq_too_late_for_merging(bfqq))
		return;

	if (bfq_class_idle(bfqq))
		return;
	if (!bfqq->next_rq)
		return;

	bfqq->pos_root = &bfq_bfqq_to_bfqg(bfqq)->rq_pos_tree;
	__bfqq = bfq_rq_pos_tree_lookup(bfqd, bfqq->pos_root,
			blk_rq_pos(bfqq->next_rq), &parent, &p);
	if (!__bfqq) {
		rb_link_node(&bfqq->pos_node, parent, p);
		rb_insert_color(&bfqq->pos_node, bfqq->pos_root);
	} else
		bfqq->pos_root = NULL;
}