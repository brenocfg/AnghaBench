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
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
struct TYPE_10__ {TYPE_3__ hdr; } ;
struct TYPE_11__ {TYPE_4__ cmd; } ;
struct nvmet_tcp_queue {int offset; TYPE_5__ pdu; int /*<<< orphan*/  idx; scalar_t__ data_digest; scalar_t__ left; int /*<<< orphan*/  sock; struct nvmet_tcp_cmd* cmd; } ;
struct TYPE_12__ {scalar_t__ transfer_len; TYPE_2__* cmd; } ;
struct nvmet_tcp_cmd {scalar_t__ recv_ddgst; scalar_t__ exp_ddgst; int flags; scalar_t__ rbytes_done; TYPE_6__ req; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; } ;
struct kvec {void* iov_base; scalar_t__ iov_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  command_id; } ;
struct TYPE_8__ {TYPE_1__ common; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EPROTO ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int NVMET_TCP_F_INIT_FAILED ; 
 int kernel_recvmsg (int /*<<< orphan*/ ,struct msghdr*,struct kvec*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  nvmet_prepare_receive_pdu (struct nvmet_tcp_queue*) ; 
 int /*<<< orphan*/  nvmet_req_execute (TYPE_6__*) ; 
 int /*<<< orphan*/  nvmet_tcp_fatal_error (struct nvmet_tcp_queue*) ; 
 int /*<<< orphan*/  nvmet_tcp_finish_cmd (struct nvmet_tcp_cmd*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvmet_tcp_try_recv_ddgst(struct nvmet_tcp_queue *queue)
{
	struct nvmet_tcp_cmd *cmd = queue->cmd;
	int ret;
	struct msghdr msg = { .msg_flags = MSG_DONTWAIT };
	struct kvec iov = {
		.iov_base = (void *)&cmd->recv_ddgst + queue->offset,
		.iov_len = queue->left
	};

	ret = kernel_recvmsg(queue->sock, &msg, &iov, 1,
			iov.iov_len, msg.msg_flags);
	if (unlikely(ret < 0))
		return ret;

	queue->offset += ret;
	queue->left -= ret;
	if (queue->left)
		return -EAGAIN;

	if (queue->data_digest && cmd->exp_ddgst != cmd->recv_ddgst) {
		pr_err("queue %d: cmd %d pdu (%d) data digest error: recv %#x expected %#x\n",
			queue->idx, cmd->req.cmd->common.command_id,
			queue->pdu.cmd.hdr.type, le32_to_cpu(cmd->recv_ddgst),
			le32_to_cpu(cmd->exp_ddgst));
		nvmet_tcp_finish_cmd(cmd);
		nvmet_tcp_fatal_error(queue);
		ret = -EPROTO;
		goto out;
	}

	if (!(cmd->flags & NVMET_TCP_F_INIT_FAILED) &&
	    cmd->rbytes_done == cmd->req.transfer_len)
		nvmet_req_execute(&cmd->req);
	ret = 0;
out:
	nvmet_prepare_receive_pdu(queue);
	return ret;
}