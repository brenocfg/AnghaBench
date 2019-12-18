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
struct nvme_tcp_data_pdu {size_t ttag; int /*<<< orphan*/  data_length; int /*<<< orphan*/  data_offset; } ;
struct TYPE_2__ {struct nvme_tcp_data_pdu data; } ;
struct nvmet_tcp_queue {int /*<<< orphan*/  rcv_state; struct nvmet_tcp_cmd* cmd; struct nvmet_tcp_cmd* cmds; TYPE_1__ pdu; } ;
struct nvmet_tcp_cmd {scalar_t__ rbytes_done; scalar_t__ pdu_recv; scalar_t__ pdu_len; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  NVMET_TCP_RECV_DATA ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_FIELD ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_req_complete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvmet_tcp_map_pdu_iovec (struct nvmet_tcp_cmd*) ; 
 int /*<<< orphan*/  pr_err (char*,size_t,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int nvmet_tcp_handle_h2c_data_pdu(struct nvmet_tcp_queue *queue)
{
	struct nvme_tcp_data_pdu *data = &queue->pdu.data;
	struct nvmet_tcp_cmd *cmd;

	cmd = &queue->cmds[data->ttag];

	if (le32_to_cpu(data->data_offset) != cmd->rbytes_done) {
		pr_err("ttag %u unexpected data offset %u (expected %u)\n",
			data->ttag, le32_to_cpu(data->data_offset),
			cmd->rbytes_done);
		/* FIXME: use path and transport errors */
		nvmet_req_complete(&cmd->req,
			NVME_SC_INVALID_FIELD | NVME_SC_DNR);
		return -EPROTO;
	}

	cmd->pdu_len = le32_to_cpu(data->data_length);
	cmd->pdu_recv = 0;
	nvmet_tcp_map_pdu_iovec(cmd);
	queue->cmd = cmd;
	queue->rcv_state = NVMET_TCP_RECV_DATA;

	return 0;
}