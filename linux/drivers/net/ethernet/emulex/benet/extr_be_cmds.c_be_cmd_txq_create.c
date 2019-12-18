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
struct be_dma_mem {int /*<<< orphan*/  size; int /*<<< orphan*/  va; } ;
struct be_queue_info {int created; int /*<<< orphan*/  id; int /*<<< orphan*/  len; struct be_dma_mem dma_mem; } ;
struct be_tx_obj {int /*<<< orphan*/  db_offset; struct be_queue_info cq; struct be_queue_info q; } ;
struct be_mcc_wrb {int /*<<< orphan*/  member_0; } ;
struct be_cmd_resp_eth_tx_create {int /*<<< orphan*/  db_offset; int /*<<< orphan*/  cid; } ;
struct TYPE_2__ {int version; } ;
struct be_cmd_req_eth_tx_create {TYPE_1__ hdr; int /*<<< orphan*/  pages; int /*<<< orphan*/  queue_size; void* cq_id; int /*<<< orphan*/  type; int /*<<< orphan*/  ulp_num; int /*<<< orphan*/  num_pages; void* if_id; } ;
struct be_adapter {int function_caps; int /*<<< orphan*/  if_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BE_ETH_TX_RING_TYPE_STANDARD ; 
 int BE_FUNCTION_CAPS_SUPER_NIC ; 
 int /*<<< orphan*/  BE_ULP1_NUM ; 
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ETH ; 
 int /*<<< orphan*/  DB_TXULP1_OFFSET ; 
 int /*<<< orphan*/  OPCODE_ETH_TX_CREATE ; 
 int /*<<< orphan*/  PAGES_4K_SPANNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_cmd_notify_wait (struct be_adapter*,struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  be_cmd_page_addrs_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_dma_mem*) ; 
 int /*<<< orphan*/  be_encoded_q_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* embedded_payload (struct be_mcc_wrb*) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

int be_cmd_txq_create(struct be_adapter *adapter, struct be_tx_obj *txo)
{
	struct be_mcc_wrb wrb = {0};
	struct be_cmd_req_eth_tx_create *req;
	struct be_queue_info *txq = &txo->q;
	struct be_queue_info *cq = &txo->cq;
	struct be_dma_mem *q_mem = &txq->dma_mem;
	int status, ver = 0;

	req = embedded_payload(&wrb);
	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ETH,
			       OPCODE_ETH_TX_CREATE, sizeof(*req), &wrb, NULL);

	if (lancer_chip(adapter)) {
		req->hdr.version = 1;
	} else if (BEx_chip(adapter)) {
		if (adapter->function_caps & BE_FUNCTION_CAPS_SUPER_NIC)
			req->hdr.version = 2;
	} else { /* For SH */
		req->hdr.version = 2;
	}

	if (req->hdr.version > 0)
		req->if_id = cpu_to_le16(adapter->if_handle);
	req->num_pages = PAGES_4K_SPANNED(q_mem->va, q_mem->size);
	req->ulp_num = BE_ULP1_NUM;
	req->type = BE_ETH_TX_RING_TYPE_STANDARD;
	req->cq_id = cpu_to_le16(cq->id);
	req->queue_size = be_encoded_q_len(txq->len);
	be_cmd_page_addrs_prepare(req->pages, ARRAY_SIZE(req->pages), q_mem);
	ver = req->hdr.version;

	status = be_cmd_notify_wait(adapter, &wrb);
	if (!status) {
		struct be_cmd_resp_eth_tx_create *resp = embedded_payload(&wrb);

		txq->id = le16_to_cpu(resp->cid);
		if (ver == 2)
			txo->db_offset = le32_to_cpu(resp->db_offset);
		else
			txo->db_offset = DB_TXULP1_OFFSET;
		txq->created = true;
	}

	return status;
}