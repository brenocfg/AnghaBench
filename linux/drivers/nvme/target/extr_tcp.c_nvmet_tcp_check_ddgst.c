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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct nvmet_tcp_queue {int /*<<< orphan*/  idx; } ;
struct nvme_tcp_hdr {int flags; scalar_t__ hlen; int /*<<< orphan*/  plen; } ;

/* Variables and functions */
 int EPROTO ; 
 int NVME_TCP_F_DDGST ; 
 int NVME_TCP_F_HDGST ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_tcp_hdgst_len (struct nvmet_tcp_queue*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvmet_tcp_check_ddgst(struct nvmet_tcp_queue *queue, void *pdu)
{
	struct nvme_tcp_hdr *hdr = pdu;
	u8 digest_len = nvmet_tcp_hdgst_len(queue);
	u32 len;

	len = le32_to_cpu(hdr->plen) - hdr->hlen -
		(hdr->flags & NVME_TCP_F_HDGST ? digest_len : 0);

	if (unlikely(len && !(hdr->flags & NVME_TCP_F_DDGST))) {
		pr_err("queue %d: data digest flag is cleared\n", queue->idx);
		return -EPROTO;
	}

	return 0;
}