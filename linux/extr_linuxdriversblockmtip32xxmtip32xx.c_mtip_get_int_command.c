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
struct request {int dummy; } ;
struct mtip_cmd {int dummy; } ;
struct driver_data {int /*<<< orphan*/  queue; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_REQ_RESERVED ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int /*<<< orphan*/  REQ_OP_DRV_IN ; 
 struct request* blk_mq_alloc_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtip_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 scalar_t__ mtip_check_surprise_removal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtip_init_cmd_header (struct request*) ; 

__attribute__((used)) static struct mtip_cmd *mtip_get_int_command(struct driver_data *dd)
{
	struct request *rq;

	if (mtip_check_surprise_removal(dd->pdev))
		return NULL;

	rq = blk_mq_alloc_request(dd->queue, REQ_OP_DRV_IN, BLK_MQ_REQ_RESERVED);
	if (IS_ERR(rq))
		return NULL;

	/* Internal cmd isn't submitted via .queue_rq */
	mtip_init_cmd_header(rq);

	return blk_mq_rq_to_pdu(rq);
}