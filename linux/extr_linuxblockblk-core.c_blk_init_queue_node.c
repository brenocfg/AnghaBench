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
struct request_queue {int /*<<< orphan*/ * request_fn; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  request_fn_proc ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct request_queue* blk_alloc_queue_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 scalar_t__ blk_init_allocated_queue (struct request_queue*) ; 

struct request_queue *
blk_init_queue_node(request_fn_proc *rfn, spinlock_t *lock, int node_id)
{
	struct request_queue *q;

	q = blk_alloc_queue_node(GFP_KERNEL, node_id, lock);
	if (!q)
		return NULL;

	q->request_fn = rfn;
	if (blk_init_allocated_queue(q) < 0) {
		blk_cleanup_queue(q);
		return NULL;
	}

	return q;
}