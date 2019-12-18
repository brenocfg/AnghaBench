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
struct isert_device {TYPE_1__* pd; struct ib_device* ib_device; } ;
struct isert_conn {struct isert_device* device; } ;
struct ib_send_wr {int dummy; } ;
struct TYPE_5__ {int num_sge; int /*<<< orphan*/  iscsi_header; struct ib_sge* tx_sg; struct ib_send_wr send_wr; } ;
struct isert_cmd {TYPE_2__ tx_desc; int /*<<< orphan*/  pdu_buf_dma; void* pdu_buf_len; } ;
struct iscsi_reject {int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {struct isert_conn* context; } ;
struct iscsi_cmd {scalar_t__ buf_ptr; } ;
struct ib_sge {int /*<<< orphan*/  lkey; void* length; int /*<<< orphan*/  addr; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 void* ISCSI_HDR_LEN ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ib_dma_map_single (struct ib_device*,void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_build_reject (struct iscsi_cmd*,struct iscsi_conn*,struct iscsi_reject*) ; 
 struct isert_cmd* iscsit_priv_cmd (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  isert_create_send_desc (struct isert_conn*,struct isert_cmd*,TYPE_2__*) ; 
 int /*<<< orphan*/  isert_dbg (char*,struct isert_conn*) ; 
 int /*<<< orphan*/  isert_init_send_wr (struct isert_conn*,struct isert_cmd*,struct ib_send_wr*) ; 
 int /*<<< orphan*/  isert_init_tx_hdrs (struct isert_conn*,TYPE_2__*) ; 
 int isert_post_response (struct isert_conn*,struct isert_cmd*) ; 

__attribute__((used)) static int
isert_put_reject(struct iscsi_cmd *cmd, struct iscsi_conn *conn)
{
	struct isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	struct isert_conn *isert_conn = conn->context;
	struct ib_send_wr *send_wr = &isert_cmd->tx_desc.send_wr;
	struct isert_device *device = isert_conn->device;
	struct ib_device *ib_dev = device->ib_device;
	struct ib_sge *tx_dsg = &isert_cmd->tx_desc.tx_sg[1];
	struct iscsi_reject *hdr =
		(struct iscsi_reject *)&isert_cmd->tx_desc.iscsi_header;

	isert_create_send_desc(isert_conn, isert_cmd, &isert_cmd->tx_desc);
	iscsit_build_reject(cmd, conn, hdr);
	isert_init_tx_hdrs(isert_conn, &isert_cmd->tx_desc);

	hton24(hdr->dlength, ISCSI_HDR_LEN);
	isert_cmd->pdu_buf_dma = ib_dma_map_single(ib_dev,
			(void *)cmd->buf_ptr, ISCSI_HDR_LEN,
			DMA_TO_DEVICE);
	if (ib_dma_mapping_error(ib_dev, isert_cmd->pdu_buf_dma))
		return -ENOMEM;
	isert_cmd->pdu_buf_len = ISCSI_HDR_LEN;
	tx_dsg->addr	= isert_cmd->pdu_buf_dma;
	tx_dsg->length	= ISCSI_HDR_LEN;
	tx_dsg->lkey	= device->pd->local_dma_lkey;
	isert_cmd->tx_desc.num_sge = 2;

	isert_init_send_wr(isert_conn, isert_cmd, send_wr);

	isert_dbg("conn %p Posting Reject\n", isert_conn);

	return isert_post_response(isert_conn, isert_cmd);
}