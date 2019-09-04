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
struct nbd_cmd {scalar_t__ status; int /*<<< orphan*/  nbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_end_request (struct request*,scalar_t__) ; 
 struct nbd_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct request*,char*) ; 
 int /*<<< orphan*/  nbd_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nbd_complete_rq(struct request *req)
{
	struct nbd_cmd *cmd = blk_mq_rq_to_pdu(req);

	dev_dbg(nbd_to_dev(cmd->nbd), "request %p: %s\n", req,
		cmd->status ? "failed" : "done");

	blk_mq_end_request(req, cmd->status);
}