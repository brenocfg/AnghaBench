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
struct TYPE_2__ {int in_use; } ;
struct t4_wq {TYPE_1__ rq; } ;
struct t4_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  insert_recv_cqe (struct t4_wq*,struct t4_cq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct t4_wq*,struct t4_cq*,int,int) ; 

int c4iw_flush_rq(struct t4_wq *wq, struct t4_cq *cq, int count)
{
	int flushed = 0;
	int in_use = wq->rq.in_use - count;

	pr_debug("wq %p cq %p rq.in_use %u skip count %u\n",
		 wq, cq, wq->rq.in_use, count);
	while (in_use--) {
		insert_recv_cqe(wq, cq, 0);
		flushed++;
	}
	return flushed;
}