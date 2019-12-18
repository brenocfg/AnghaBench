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
struct request {int dummy; } ;
struct nvme_tcp_request {scalar_t__ data_len; struct nvme_tcp_cmd_pdu* pdu; } ;
struct nvme_tcp_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct nvme_command {TYPE_1__ common; } ;
struct nvme_tcp_cmd_pdu {struct nvme_command cmd; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_CMD_SGL_METABUF ; 
 scalar_t__ WRITE ; 
 struct nvme_tcp_request* blk_mq_rq_to_pdu (struct request*) ; 
 scalar_t__ nvme_tcp_inline_data_size (struct nvme_tcp_queue*) ; 
 int /*<<< orphan*/  nvme_tcp_set_sg_host_data (struct nvme_command*,scalar_t__) ; 
 int /*<<< orphan*/  nvme_tcp_set_sg_inline (struct nvme_tcp_queue*,struct nvme_command*,scalar_t__) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static blk_status_t nvme_tcp_map_data(struct nvme_tcp_queue *queue,
			struct request *rq)
{
	struct nvme_tcp_request *req = blk_mq_rq_to_pdu(rq);
	struct nvme_tcp_cmd_pdu *pdu = req->pdu;
	struct nvme_command *c = &pdu->cmd;

	c->common.flags |= NVME_CMD_SGL_METABUF;

	if (rq_data_dir(rq) == WRITE && req->data_len &&
	    req->data_len <= nvme_tcp_inline_data_size(queue))
		nvme_tcp_set_sg_inline(queue, c, req->data_len);
	else
		nvme_tcp_set_sg_host_data(c, req->data_len);

	return 0;
}