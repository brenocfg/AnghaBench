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
struct blk_flush_queue {struct blk_flush_queue* flush_rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct blk_flush_queue*) ; 

void blk_free_flush_queue(struct blk_flush_queue *fq)
{
	/* bio based request queue hasn't flush queue */
	if (!fq)
		return;

	kfree(fq->flush_rq);
	kfree(fq);
}