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
struct nvme_tcp_request {int offset; int /*<<< orphan*/  ddgst; struct nvme_tcp_queue* queue; } ;
struct nvme_tcp_queue {int /*<<< orphan*/  sock; } ;
struct msghdr {int msg_flags; } ;
struct kvec {scalar_t__ iov_len; int /*<<< orphan*/ * iov_base; } ;

/* Variables and functions */
 int EAGAIN ; 
 int MSG_DONTWAIT ; 
 int MSG_EOR ; 
 scalar_t__ NVME_TCP_DIGEST_LENGTH ; 
 int kernel_sendmsg (int /*<<< orphan*/ ,struct msghdr*,struct kvec*,int,scalar_t__) ; 
 int /*<<< orphan*/  nvme_tcp_done_send_req (struct nvme_tcp_queue*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvme_tcp_try_send_ddgst(struct nvme_tcp_request *req)
{
	struct nvme_tcp_queue *queue = req->queue;
	int ret;
	struct msghdr msg = { .msg_flags = MSG_DONTWAIT | MSG_EOR };
	struct kvec iov = {
		.iov_base = &req->ddgst + req->offset,
		.iov_len = NVME_TCP_DIGEST_LENGTH - req->offset
	};

	ret = kernel_sendmsg(queue->sock, &msg, &iov, 1, iov.iov_len);
	if (unlikely(ret <= 0))
		return ret;

	if (req->offset + ret == NVME_TCP_DIGEST_LENGTH) {
		nvme_tcp_done_send_req(queue);
		return 1;
	}

	req->offset += ret;
	return -EAGAIN;
}