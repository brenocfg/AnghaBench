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
struct nvme_tcp_queue {scalar_t__ hdr_digest; scalar_t__ data_digest; int /*<<< orphan*/  sock; } ;
struct TYPE_2__ {scalar_t__ type; int hlen; scalar_t__ plen; scalar_t__ pdo; } ;
struct nvme_tcp_icresp_pdu {scalar_t__ pfv; int digest; scalar_t__ cpda; TYPE_1__ hdr; scalar_t__ hpda; scalar_t__ maxr2t; } ;
struct nvme_tcp_icreq_pdu {scalar_t__ pfv; int digest; scalar_t__ cpda; TYPE_1__ hdr; scalar_t__ hpda; scalar_t__ maxr2t; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; } ;
struct kvec {int iov_len; struct nvme_tcp_icresp_pdu* iov_base; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NVME_TCP_DATA_DIGEST_ENABLE ; 
 int NVME_TCP_HDR_DIGEST_ENABLE ; 
 scalar_t__ NVME_TCP_PFV_1_0 ; 
 scalar_t__ cpu_to_le16 (scalar_t__) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int kernel_recvmsg (int /*<<< orphan*/ ,struct msghdr*,struct kvec*,int,int,int /*<<< orphan*/ ) ; 
 int kernel_sendmsg (int /*<<< orphan*/ ,struct msghdr*,struct kvec*,int,int) ; 
 int /*<<< orphan*/  kfree (struct nvme_tcp_icresp_pdu*) ; 
 struct nvme_tcp_icresp_pdu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_tcp_icreq ; 
 scalar_t__ nvme_tcp_icresp ; 
 int /*<<< orphan*/  nvme_tcp_queue_id (struct nvme_tcp_queue*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 

__attribute__((used)) static int nvme_tcp_init_connection(struct nvme_tcp_queue *queue)
{
	struct nvme_tcp_icreq_pdu *icreq;
	struct nvme_tcp_icresp_pdu *icresp;
	struct msghdr msg = {};
	struct kvec iov;
	bool ctrl_hdgst, ctrl_ddgst;
	int ret;

	icreq = kzalloc(sizeof(*icreq), GFP_KERNEL);
	if (!icreq)
		return -ENOMEM;

	icresp = kzalloc(sizeof(*icresp), GFP_KERNEL);
	if (!icresp) {
		ret = -ENOMEM;
		goto free_icreq;
	}

	icreq->hdr.type = nvme_tcp_icreq;
	icreq->hdr.hlen = sizeof(*icreq);
	icreq->hdr.pdo = 0;
	icreq->hdr.plen = cpu_to_le32(icreq->hdr.hlen);
	icreq->pfv = cpu_to_le16(NVME_TCP_PFV_1_0);
	icreq->maxr2t = 0; /* single inflight r2t supported */
	icreq->hpda = 0; /* no alignment constraint */
	if (queue->hdr_digest)
		icreq->digest |= NVME_TCP_HDR_DIGEST_ENABLE;
	if (queue->data_digest)
		icreq->digest |= NVME_TCP_DATA_DIGEST_ENABLE;

	iov.iov_base = icreq;
	iov.iov_len = sizeof(*icreq);
	ret = kernel_sendmsg(queue->sock, &msg, &iov, 1, iov.iov_len);
	if (ret < 0)
		goto free_icresp;

	memset(&msg, 0, sizeof(msg));
	iov.iov_base = icresp;
	iov.iov_len = sizeof(*icresp);
	ret = kernel_recvmsg(queue->sock, &msg, &iov, 1,
			iov.iov_len, msg.msg_flags);
	if (ret < 0)
		goto free_icresp;

	ret = -EINVAL;
	if (icresp->hdr.type != nvme_tcp_icresp) {
		pr_err("queue %d: bad type returned %d\n",
			nvme_tcp_queue_id(queue), icresp->hdr.type);
		goto free_icresp;
	}

	if (le32_to_cpu(icresp->hdr.plen) != sizeof(*icresp)) {
		pr_err("queue %d: bad pdu length returned %d\n",
			nvme_tcp_queue_id(queue), icresp->hdr.plen);
		goto free_icresp;
	}

	if (icresp->pfv != NVME_TCP_PFV_1_0) {
		pr_err("queue %d: bad pfv returned %d\n",
			nvme_tcp_queue_id(queue), icresp->pfv);
		goto free_icresp;
	}

	ctrl_ddgst = !!(icresp->digest & NVME_TCP_DATA_DIGEST_ENABLE);
	if ((queue->data_digest && !ctrl_ddgst) ||
	    (!queue->data_digest && ctrl_ddgst)) {
		pr_err("queue %d: data digest mismatch host: %s ctrl: %s\n",
			nvme_tcp_queue_id(queue),
			queue->data_digest ? "enabled" : "disabled",
			ctrl_ddgst ? "enabled" : "disabled");
		goto free_icresp;
	}

	ctrl_hdgst = !!(icresp->digest & NVME_TCP_HDR_DIGEST_ENABLE);
	if ((queue->hdr_digest && !ctrl_hdgst) ||
	    (!queue->hdr_digest && ctrl_hdgst)) {
		pr_err("queue %d: header digest mismatch host: %s ctrl: %s\n",
			nvme_tcp_queue_id(queue),
			queue->hdr_digest ? "enabled" : "disabled",
			ctrl_hdgst ? "enabled" : "disabled");
		goto free_icresp;
	}

	if (icresp->cpda != 0) {
		pr_err("queue %d: unsupported cpda returned %d\n",
			nvme_tcp_queue_id(queue), icresp->cpda);
		goto free_icresp;
	}

	ret = 0;
free_icresp:
	kfree(icresp);
free_icreq:
	kfree(icreq);
	return ret;
}