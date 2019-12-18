#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct nvme_tcp_queue {int /*<<< orphan*/  rcv_hash; TYPE_2__* ctrl; } ;
struct nvme_tcp_hdr {int flags; scalar_t__ hlen; int /*<<< orphan*/  plen; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ ctrl; } ;

/* Variables and functions */
 int EPROTO ; 
 int NVME_TCP_F_DDGST ; 
 int NVME_TCP_F_HDGST ; 
 int /*<<< orphan*/  crypto_ahash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_tcp_hdgst_len (struct nvme_tcp_queue*) ; 
 int /*<<< orphan*/  nvme_tcp_queue_id (struct nvme_tcp_queue*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvme_tcp_check_ddgst(struct nvme_tcp_queue *queue, void *pdu)
{
	struct nvme_tcp_hdr *hdr = pdu;
	u8 digest_len = nvme_tcp_hdgst_len(queue);
	u32 len;

	len = le32_to_cpu(hdr->plen) - hdr->hlen -
		((hdr->flags & NVME_TCP_F_HDGST) ? digest_len : 0);

	if (unlikely(len && !(hdr->flags & NVME_TCP_F_DDGST))) {
		dev_err(queue->ctrl->ctrl.device,
			"queue %d: data digest flag is cleared\n",
		nvme_tcp_queue_id(queue));
		return -EPROTO;
	}
	crypto_ahash_init(queue->rcv_hash);

	return 0;
}