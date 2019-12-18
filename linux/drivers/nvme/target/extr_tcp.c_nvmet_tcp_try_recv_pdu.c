#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct nvme_tcp_hdr {scalar_t__ hlen; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {struct nvme_tcp_hdr hdr; } ;
struct TYPE_5__ {TYPE_1__ cmd; } ;
struct nvmet_tcp_queue {int offset; scalar_t__ left; TYPE_2__ pdu; scalar_t__ data_digest; scalar_t__ hdr_digest; int /*<<< orphan*/  sock; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; } ;
struct kvec {scalar_t__ iov_len; void* iov_base; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int EPROTO ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int kernel_recvmsg (int /*<<< orphan*/ ,struct msghdr*,struct kvec*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nvmet_tcp_check_ddgst (struct nvmet_tcp_queue*,TYPE_2__*) ; 
 int nvmet_tcp_done_recv_pdu (struct nvmet_tcp_queue*) ; 
 int /*<<< orphan*/  nvmet_tcp_fatal_error (struct nvmet_tcp_queue*) ; 
 scalar_t__ nvmet_tcp_hdgst_len (struct nvmet_tcp_queue*) ; 
 scalar_t__ nvmet_tcp_pdu_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_tcp_pdu_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ nvmet_tcp_verify_hdgst (struct nvmet_tcp_queue*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvmet_tcp_try_recv_pdu(struct nvmet_tcp_queue *queue)
{
	struct nvme_tcp_hdr *hdr = &queue->pdu.cmd.hdr;
	int len;
	struct kvec iov;
	struct msghdr msg = { .msg_flags = MSG_DONTWAIT };

recv:
	iov.iov_base = (void *)&queue->pdu + queue->offset;
	iov.iov_len = queue->left;
	len = kernel_recvmsg(queue->sock, &msg, &iov, 1,
			iov.iov_len, msg.msg_flags);
	if (unlikely(len < 0))
		return len;

	queue->offset += len;
	queue->left -= len;
	if (queue->left)
		return -EAGAIN;

	if (queue->offset == sizeof(struct nvme_tcp_hdr)) {
		u8 hdgst = nvmet_tcp_hdgst_len(queue);

		if (unlikely(!nvmet_tcp_pdu_valid(hdr->type))) {
			pr_err("unexpected pdu type %d\n", hdr->type);
			nvmet_tcp_fatal_error(queue);
			return -EIO;
		}

		if (unlikely(hdr->hlen != nvmet_tcp_pdu_size(hdr->type))) {
			pr_err("pdu %d bad hlen %d\n", hdr->type, hdr->hlen);
			return -EIO;
		}

		queue->left = hdr->hlen - queue->offset + hdgst;
		goto recv;
	}

	if (queue->hdr_digest &&
	    nvmet_tcp_verify_hdgst(queue, &queue->pdu, queue->offset)) {
		nvmet_tcp_fatal_error(queue); /* fatal */
		return -EPROTO;
	}

	if (queue->data_digest &&
	    nvmet_tcp_check_ddgst(queue, &queue->pdu)) {
		nvmet_tcp_fatal_error(queue); /* fatal */
		return -EPROTO;
	}

	return nvmet_tcp_done_recv_pdu(queue);
}