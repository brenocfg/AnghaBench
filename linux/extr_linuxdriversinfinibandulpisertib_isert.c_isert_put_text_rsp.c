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
typedef  int u32 ;
struct isert_device {TYPE_1__* pd; struct ib_device* ib_device; } ;
struct isert_conn {struct isert_device* device; } ;
struct ib_send_wr {int dummy; } ;
struct TYPE_5__ {int num_sge; struct ib_sge* tx_sg; int /*<<< orphan*/  iscsi_header; struct ib_send_wr send_wr; } ;
struct isert_cmd {int pdu_buf_len; TYPE_2__ tx_desc; int /*<<< orphan*/  pdu_buf_dma; } ;
struct iscsi_text_rsp {int dummy; } ;
struct iscsi_conn {struct isert_conn* context; } ;
struct iscsi_cmd {void* buf_ptr; } ;
struct ib_sge {int length; int /*<<< orphan*/  lkey; int /*<<< orphan*/  addr; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ISCSI_INFINIBAND ; 
 int /*<<< orphan*/  ib_dma_map_single (struct ib_device*,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (struct ib_device*,int /*<<< orphan*/ ) ; 
 int iscsit_build_text_rsp (struct iscsi_cmd*,struct iscsi_conn*,struct iscsi_text_rsp*,int /*<<< orphan*/ ) ; 
 struct isert_cmd* iscsit_priv_cmd (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  isert_create_send_desc (struct isert_conn*,struct isert_cmd*,TYPE_2__*) ; 
 int /*<<< orphan*/  isert_dbg (char*,struct isert_conn*) ; 
 int /*<<< orphan*/  isert_init_send_wr (struct isert_conn*,struct isert_cmd*,struct ib_send_wr*) ; 
 int /*<<< orphan*/  isert_init_tx_hdrs (struct isert_conn*,TYPE_2__*) ; 
 int isert_post_response (struct isert_conn*,struct isert_cmd*) ; 

__attribute__((used)) static int
isert_put_text_rsp(struct iscsi_cmd *cmd, struct iscsi_conn *conn)
{
	struct isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	struct isert_conn *isert_conn = conn->context;
	struct ib_send_wr *send_wr = &isert_cmd->tx_desc.send_wr;
	struct iscsi_text_rsp *hdr =
		(struct iscsi_text_rsp *)&isert_cmd->tx_desc.iscsi_header;
	u32 txt_rsp_len;
	int rc;

	isert_create_send_desc(isert_conn, isert_cmd, &isert_cmd->tx_desc);
	rc = iscsit_build_text_rsp(cmd, conn, hdr, ISCSI_INFINIBAND);
	if (rc < 0)
		return rc;

	txt_rsp_len = rc;
	isert_init_tx_hdrs(isert_conn, &isert_cmd->tx_desc);

	if (txt_rsp_len) {
		struct isert_device *device = isert_conn->device;
		struct ib_device *ib_dev = device->ib_device;
		struct ib_sge *tx_dsg = &isert_cmd->tx_desc.tx_sg[1];
		void *txt_rsp_buf = cmd->buf_ptr;

		isert_cmd->pdu_buf_dma = ib_dma_map_single(ib_dev,
				txt_rsp_buf, txt_rsp_len, DMA_TO_DEVICE);
		if (ib_dma_mapping_error(ib_dev, isert_cmd->pdu_buf_dma))
			return -ENOMEM;

		isert_cmd->pdu_buf_len = txt_rsp_len;
		tx_dsg->addr	= isert_cmd->pdu_buf_dma;
		tx_dsg->length	= txt_rsp_len;
		tx_dsg->lkey	= device->pd->local_dma_lkey;
		isert_cmd->tx_desc.num_sge = 2;
	}
	isert_init_send_wr(isert_conn, isert_cmd, send_wr);

	isert_dbg("conn %p Text Response\n", isert_conn);

	return isert_post_response(isert_conn, isert_cmd);
}