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
struct rq_wb {int /*<<< orphan*/  cb; } ;
struct rq_qos {struct request_queue* q; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 struct rq_wb* RQWB (struct rq_qos*) ; 
 int /*<<< orphan*/  blk_stat_free_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_stat_remove_callback (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rq_wb*) ; 

__attribute__((used)) static void wbt_exit(struct rq_qos *rqos)
{
	struct rq_wb *rwb = RQWB(rqos);
	struct request_queue *q = rqos->q;

	blk_stat_remove_callback(q, rwb->cb);
	blk_stat_free_callback(rwb->cb);
	kfree(rwb);
}