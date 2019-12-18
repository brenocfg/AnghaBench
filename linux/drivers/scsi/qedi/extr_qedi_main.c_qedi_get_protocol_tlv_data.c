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
typedef  int u32 ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  ll2_mtu; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  cdev; } ;
struct qed_mfw_tlv_iscsi {int rx_frames_set; int rx_bytes_set; int tx_frames_set; int tx_bytes_set; int frame_size_set; int auth_method_set; int auth_method; int tx_desc_size_set; int rx_desc_size_set; int /*<<< orphan*/  rx_desc_size; int /*<<< orphan*/  tx_desc_size; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_frames; } ;
struct qed_iscsi_stats {int /*<<< orphan*/  iscsi_tx_bytes_cnt; int /*<<< orphan*/  iscsi_tx_packet_cnt; int /*<<< orphan*/  iscsi_rx_bytes_cnt; int /*<<< orphan*/  iscsi_rx_packet_cnt; } ;
struct TYPE_3__ {int ctrl_flags; } ;
struct nvm_iscsi_block {TYPE_1__ generic; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_stats ) (int /*<<< orphan*/ ,struct qed_iscsi_stats*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NVM_ISCSI_CFG_GEN_CHAP_ENABLED ; 
 int NVM_ISCSI_CFG_GEN_CHAP_MUTUAL_ENABLED ; 
 int /*<<< orphan*/  QEDI_CQ_SIZE ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDI_LOG_INFO ; 
 int /*<<< orphan*/  QEDI_SQ_SIZE ; 
 int /*<<< orphan*/  kfree (struct qed_iscsi_stats*) ; 
 struct qed_iscsi_stats* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qedi_find_boot_info (struct qedi_ctx*,struct qed_mfw_tlv_iscsi*,struct nvm_iscsi_block*) ; 
 struct nvm_iscsi_block* qedi_get_nvram_block (struct qedi_ctx*) ; 
 TYPE_2__* qedi_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_iscsi_stats*) ; 

__attribute__((used)) static void qedi_get_protocol_tlv_data(void *dev, void *data)
{
	struct qed_mfw_tlv_iscsi *iscsi = data;
	struct qed_iscsi_stats *fw_iscsi_stats;
	struct nvm_iscsi_block *block = NULL;
	u32 chap_en = 0, mchap_en = 0;
	struct qedi_ctx *qedi = dev;
	int rval = 0;

	fw_iscsi_stats = kmalloc(sizeof(*fw_iscsi_stats), GFP_KERNEL);
	if (!fw_iscsi_stats) {
		QEDI_ERR(&qedi->dbg_ctx,
			 "Could not allocate memory for fw_iscsi_stats.\n");
		goto exit_get_data;
	}

	mutex_lock(&qedi->stats_lock);
	/* Query firmware for offload stats */
	qedi_ops->get_stats(qedi->cdev, fw_iscsi_stats);
	mutex_unlock(&qedi->stats_lock);

	iscsi->rx_frames_set = true;
	iscsi->rx_frames = fw_iscsi_stats->iscsi_rx_packet_cnt;
	iscsi->rx_bytes_set = true;
	iscsi->rx_bytes = fw_iscsi_stats->iscsi_rx_bytes_cnt;
	iscsi->tx_frames_set = true;
	iscsi->tx_frames = fw_iscsi_stats->iscsi_tx_packet_cnt;
	iscsi->tx_bytes_set = true;
	iscsi->tx_bytes = fw_iscsi_stats->iscsi_tx_bytes_cnt;
	iscsi->frame_size_set = true;
	iscsi->frame_size = qedi->ll2_mtu;
	block = qedi_get_nvram_block(qedi);
	if (block) {
		chap_en = !!(block->generic.ctrl_flags &
			     NVM_ISCSI_CFG_GEN_CHAP_ENABLED);
		mchap_en = !!(block->generic.ctrl_flags &
			      NVM_ISCSI_CFG_GEN_CHAP_MUTUAL_ENABLED);

		iscsi->auth_method_set = (chap_en || mchap_en) ? true : false;
		iscsi->auth_method = 1;
		if (chap_en)
			iscsi->auth_method = 2;
		if (mchap_en)
			iscsi->auth_method = 3;

		iscsi->tx_desc_size_set = true;
		iscsi->tx_desc_size = QEDI_SQ_SIZE;
		iscsi->rx_desc_size_set = true;
		iscsi->rx_desc_size = QEDI_CQ_SIZE;

		/* tpgt, hdr digest, data digest */
		rval = qedi_find_boot_info(qedi, iscsi, block);
		if (rval)
			QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
				  "Boot target not set");
	}

	kfree(fw_iscsi_stats);
exit_get_data:
	return;
}