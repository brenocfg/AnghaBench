#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nvmet_tcp_queue {int /*<<< orphan*/  rcv_state; int /*<<< orphan*/  idx; } ;
struct TYPE_8__ {TYPE_1__* port; int /*<<< orphan*/  cmd; } ;
struct nvmet_tcp_cmd {int /*<<< orphan*/  flags; TYPE_2__ req; } ;
struct nvmet_req {scalar_t__ data_len; TYPE_6__* cmd; } ;
struct TYPE_9__ {int /*<<< orphan*/  length; } ;
struct TYPE_11__ {TYPE_3__ sgl; } ;
struct TYPE_10__ {TYPE_5__ dptr; } ;
struct TYPE_12__ {TYPE_4__ common; } ;
struct TYPE_7__ {scalar_t__ inline_data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVMET_TCP_F_INIT_FAILED ; 
 int /*<<< orphan*/  NVMET_TCP_RECV_DATA ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_is_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_prepare_receive_pdu (struct nvmet_tcp_queue*) ; 
 int /*<<< orphan*/  nvmet_tcp_fatal_error (struct nvmet_tcp_queue*) ; 
 int nvmet_tcp_map_data (struct nvmet_tcp_cmd*) ; 
 int /*<<< orphan*/  nvmet_tcp_map_pdu_iovec (struct nvmet_tcp_cmd*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void nvmet_tcp_handle_req_failure(struct nvmet_tcp_queue *queue,
		struct nvmet_tcp_cmd *cmd, struct nvmet_req *req)
{
	int ret;

	/* recover the expected data transfer length */
	req->data_len = le32_to_cpu(req->cmd->common.dptr.sgl.length);

	if (!nvme_is_write(cmd->req.cmd) ||
	    req->data_len > cmd->req.port->inline_data_size) {
		nvmet_prepare_receive_pdu(queue);
		return;
	}

	ret = nvmet_tcp_map_data(cmd);
	if (unlikely(ret)) {
		pr_err("queue %d: failed to map data\n", queue->idx);
		nvmet_tcp_fatal_error(queue);
		return;
	}

	queue->rcv_state = NVMET_TCP_RECV_DATA;
	nvmet_tcp_map_pdu_iovec(cmd);
	cmd->flags |= NVMET_TCP_F_INIT_FAILED;
}