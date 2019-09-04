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
struct nbd_cmd {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  blk_mq_complete_request (struct request*) ; 
 struct nbd_cmd* blk_mq_rq_to_pdu (struct request*) ; 

__attribute__((used)) static void nbd_clear_req(struct request *req, void *data, bool reserved)
{
	struct nbd_cmd *cmd = blk_mq_rq_to_pdu(req);

	cmd->status = BLK_STS_IOERR;
	blk_mq_complete_request(req);
}