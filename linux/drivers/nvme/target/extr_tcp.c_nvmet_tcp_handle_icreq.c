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
struct TYPE_6__ {int hlen; void* plen; scalar_t__ pdo; int /*<<< orphan*/  type; } ;
struct nvme_tcp_icresp_pdu {int digest; scalar_t__ cpda; void* maxdata; int /*<<< orphan*/  pfv; TYPE_3__ hdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  plen; } ;
struct nvme_tcp_icreq_pdu {scalar_t__ pfv; scalar_t__ hpda; int digest; TYPE_2__ hdr; } ;
struct TYPE_4__ {struct nvme_tcp_icresp_pdu icresp; struct nvme_tcp_icreq_pdu icreq; } ;
struct nvmet_tcp_queue {int hdr_digest; int data_digest; int /*<<< orphan*/  state; int /*<<< orphan*/  sock; int /*<<< orphan*/  idx; TYPE_1__ pdu; } ;
struct msghdr {int dummy; } ;
struct kvec {int iov_len; struct nvme_tcp_icresp_pdu* iov_base; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  NVMET_TCP_Q_LIVE ; 
 int NVME_TCP_DATA_DIGEST_ENABLE ; 
 int NVME_TCP_HDR_DIGEST_ENABLE ; 
 scalar_t__ NVME_TCP_PFV_1_0 ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int) ; 
 int kernel_sendmsg (int /*<<< orphan*/ ,struct msghdr*,struct kvec*,int,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_tcp_icresp_pdu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_tcp_icresp ; 
 int /*<<< orphan*/  nvmet_prepare_receive_pdu (struct nvmet_tcp_queue*) ; 
 int nvmet_tcp_alloc_crypto (struct nvmet_tcp_queue*) ; 
 int /*<<< orphan*/  nvmet_tcp_fatal_error (struct nvmet_tcp_queue*) ; 
 int /*<<< orphan*/  nvmet_tcp_free_crypto (struct nvmet_tcp_queue*) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

__attribute__((used)) static int nvmet_tcp_handle_icreq(struct nvmet_tcp_queue *queue)
{
	struct nvme_tcp_icreq_pdu *icreq = &queue->pdu.icreq;
	struct nvme_tcp_icresp_pdu *icresp = &queue->pdu.icresp;
	struct msghdr msg = {};
	struct kvec iov;
	int ret;

	if (le32_to_cpu(icreq->hdr.plen) != sizeof(struct nvme_tcp_icreq_pdu)) {
		pr_err("bad nvme-tcp pdu length (%d)\n",
			le32_to_cpu(icreq->hdr.plen));
		nvmet_tcp_fatal_error(queue);
	}

	if (icreq->pfv != NVME_TCP_PFV_1_0) {
		pr_err("queue %d: bad pfv %d\n", queue->idx, icreq->pfv);
		return -EPROTO;
	}

	if (icreq->hpda != 0) {
		pr_err("queue %d: unsupported hpda %d\n", queue->idx,
			icreq->hpda);
		return -EPROTO;
	}

	queue->hdr_digest = !!(icreq->digest & NVME_TCP_HDR_DIGEST_ENABLE);
	queue->data_digest = !!(icreq->digest & NVME_TCP_DATA_DIGEST_ENABLE);
	if (queue->hdr_digest || queue->data_digest) {
		ret = nvmet_tcp_alloc_crypto(queue);
		if (ret)
			return ret;
	}

	memset(icresp, 0, sizeof(*icresp));
	icresp->hdr.type = nvme_tcp_icresp;
	icresp->hdr.hlen = sizeof(*icresp);
	icresp->hdr.pdo = 0;
	icresp->hdr.plen = cpu_to_le32(icresp->hdr.hlen);
	icresp->pfv = cpu_to_le16(NVME_TCP_PFV_1_0);
	icresp->maxdata = cpu_to_le32(0xffff); /* FIXME: support r2t */
	icresp->cpda = 0;
	if (queue->hdr_digest)
		icresp->digest |= NVME_TCP_HDR_DIGEST_ENABLE;
	if (queue->data_digest)
		icresp->digest |= NVME_TCP_DATA_DIGEST_ENABLE;

	iov.iov_base = icresp;
	iov.iov_len = sizeof(*icresp);
	ret = kernel_sendmsg(queue->sock, &msg, &iov, 1, iov.iov_len);
	if (ret < 0)
		goto free_crypto;

	queue->state = NVMET_TCP_Q_LIVE;
	nvmet_prepare_receive_pdu(queue);
	return 0;
free_crypto:
	if (queue->hdr_digest || queue->data_digest)
		nvmet_tcp_free_crypto(queue);
	return ret;
}