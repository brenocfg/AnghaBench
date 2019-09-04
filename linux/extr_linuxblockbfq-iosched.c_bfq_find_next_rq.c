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
struct rb_node {int dummy; } ;
struct request {struct rb_node rb_node; } ;
struct bfq_queue {int /*<<< orphan*/  sort_list; } ;
struct bfq_data {int dummy; } ;

/* Variables and functions */
 struct request* bfq_check_fifo (struct bfq_queue*,struct request*) ; 
 struct request* bfq_choose_req (struct bfq_data*,struct request*,struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 struct request* rb_entry_rq (struct rb_node*) ; 
 struct rb_node* rb_first (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 struct rb_node* rb_prev (struct rb_node*) ; 

__attribute__((used)) static struct request *bfq_find_next_rq(struct bfq_data *bfqd,
					struct bfq_queue *bfqq,
					struct request *last)
{
	struct rb_node *rbnext = rb_next(&last->rb_node);
	struct rb_node *rbprev = rb_prev(&last->rb_node);
	struct request *next, *prev = NULL;

	/* Follow expired path, else get first next available. */
	next = bfq_check_fifo(bfqq, last);
	if (next)
		return next;

	if (rbprev)
		prev = rb_entry_rq(rbprev);

	if (rbnext)
		next = rb_entry_rq(rbnext);
	else {
		rbnext = rb_first(&bfqq->sort_list);
		if (rbnext && rbnext != &last->rb_node)
			next = rb_entry_rq(rbnext);
	}

	return bfq_choose_req(bfqd, next, prev, blk_rq_pos(last));
}