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
struct work_struct {int dummy; } ;
struct request {int dummy; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 struct work_struct* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,struct work_struct*) ; 
 int /*<<< orphan*/  rbd_wq ; 

__attribute__((used)) static blk_status_t rbd_queue_rq(struct blk_mq_hw_ctx *hctx,
		const struct blk_mq_queue_data *bd)
{
	struct request *rq = bd->rq;
	struct work_struct *work = blk_mq_rq_to_pdu(rq);

	queue_work(rbd_wq, work);
	return BLK_STS_OK;
}