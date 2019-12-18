#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct request_queue {int dummy; } ;
struct request {struct nvme_queue* end_io_data; int /*<<< orphan*/  timeout; } ;
struct nvme_queue {int /*<<< orphan*/  delete_done; int /*<<< orphan*/  qid; TYPE_3__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  qid; scalar_t__ opcode; } ;
struct nvme_command {TYPE_1__ delete_queue; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {struct request_queue* admin_q; } ;
struct TYPE_6__ {TYPE_2__ ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMIN_TIMEOUT ; 
 int /*<<< orphan*/  BLK_MQ_REQ_NOWAIT ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int /*<<< orphan*/  NVME_QID_ANY ; 
 int PTR_ERR (struct request*) ; 
 int /*<<< orphan*/  blk_execute_rq_nowait (struct request_queue*,int /*<<< orphan*/ *,struct request*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_admin_delete_cq ; 
 struct request* nvme_alloc_request (struct request_queue*,struct nvme_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_del_cq_end ; 
 int /*<<< orphan*/  nvme_del_queue_end ; 

__attribute__((used)) static int nvme_delete_queue(struct nvme_queue *nvmeq, u8 opcode)
{
	struct request_queue *q = nvmeq->dev->ctrl.admin_q;
	struct request *req;
	struct nvme_command cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.delete_queue.opcode = opcode;
	cmd.delete_queue.qid = cpu_to_le16(nvmeq->qid);

	req = nvme_alloc_request(q, &cmd, BLK_MQ_REQ_NOWAIT, NVME_QID_ANY);
	if (IS_ERR(req))
		return PTR_ERR(req);

	req->timeout = ADMIN_TIMEOUT;
	req->end_io_data = nvmeq;

	init_completion(&nvmeq->delete_done);
	blk_execute_rq_nowait(q, NULL, req, false,
			opcode == nvme_admin_delete_cq ?
				nvme_del_cq_end : nvme_del_queue_end);
	return 0;
}