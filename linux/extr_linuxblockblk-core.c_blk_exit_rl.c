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
struct request_list {scalar_t__ rq_pool; } ;
struct request_queue {struct request_list root_rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_put_queue (struct request_queue*) ; 
 int /*<<< orphan*/  mempool_destroy (scalar_t__) ; 

void blk_exit_rl(struct request_queue *q, struct request_list *rl)
{
	if (rl->rq_pool) {
		mempool_destroy(rl->rq_pool);
		if (rl != &q->root_rl)
			blk_put_queue(q);
	}
}