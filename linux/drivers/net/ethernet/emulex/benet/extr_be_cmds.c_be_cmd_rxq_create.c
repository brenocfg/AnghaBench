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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct be_dma_mem {int dummy; } ;
struct be_queue_info {int created; int /*<<< orphan*/  id; struct be_dma_mem dma_mem; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_resp_eth_rx_create {int /*<<< orphan*/  rss_id; int /*<<< orphan*/  id; } ;
struct be_cmd_req_eth_rx_create {int num_pages; void* rss_queue; void* max_frame_size; void* interface_id; int /*<<< orphan*/  pages; scalar_t__ frag_size; void* cq_id; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BE_MAX_JUMBO_FRAME_SIZE ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ETH ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_ETH_RX_CREATE ; 
 int /*<<< orphan*/  be_cmd_page_addrs_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_dma_mem*) ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* embedded_payload (struct be_mcc_wrb*) ; 
 scalar_t__ fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_rxq_create(struct be_adapter *adapter,
		      struct be_queue_info *rxq, u16 cq_id, u16 frag_size,
		      u32 if_id, u32 rss, u8 *rss_id)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_eth_rx_create *req;
	struct be_dma_mem *q_mem = &rxq->dma_mem;
	int status;

	mutex_lock(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ETH,
			       OPCODE_ETH_RX_CREATE, sizeof(*req), wrb, NULL);

	req->cq_id = cpu_to_le16(cq_id);
	req->frag_size = fls(frag_size) - 1;
	req->num_pages = 2;
	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);
	req->interface_id = cpu_to_le32(if_id);
	req->max_frame_size = cpu_to_le16(BE_MAX_JUMBO_FRAME_SIZE);
	req->rss_queue = cpu_to_le32(rss);

	status = be_mcc_notify_wait(adapter);
	if (!status) {
		struct be_cmd_resp_eth_rx_create *resp = embedded_payload(wrb);

		rxq->id = le16_to_cpu(resp->id);
		rxq->created = true;
		*rss_id = resp->rss_id;
	}

err:
	mutex_unlock(&adapter->mcc_lock);
	return status;
}