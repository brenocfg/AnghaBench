#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct iwl_trans_pcie {int rx_buf_size; size_t cmd_queue; int /*<<< orphan*/  ctxt_info_dma_addr; struct iwl_context_info* ctxt_info; TYPE_4__** txq; TYPE_3__* rxq; } ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;
struct iwl_context_info_rbd_cfg {void* status_wr_ptr; void* used_rbd_addr; void* free_rbd_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  cmd_queue_size; void* cmd_queue_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  control_flags; } ;
struct TYPE_6__ {void* size; void* mac_id; scalar_t__ version; } ;
struct iwl_context_info {int /*<<< orphan*/  dram; TYPE_5__ hcmd_cfg; struct iwl_context_info_rbd_cfg rbd_cfg; TYPE_2__ control; TYPE_1__ version; } ;
struct fw_img {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dma_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  rb_stts_dma; int /*<<< orphan*/  used_bd_dma; int /*<<< orphan*/  bd_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CSR_CTXT_INFO_BA ; 
 int /*<<< orphan*/  CSR_HW_REV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IWL_AMSDU_12K 131 
#define  IWL_AMSDU_2K 130 
#define  IWL_AMSDU_4K 129 
#define  IWL_AMSDU_8K 128 
 int /*<<< orphan*/  IWL_CMD_QUEUE_SIZE ; 
 int IWL_CTXT_INFO_RB_CB_SIZE_POS ; 
 int IWL_CTXT_INFO_RB_SIZE_12K ; 
 int IWL_CTXT_INFO_RB_SIZE_2K ; 
 int IWL_CTXT_INFO_RB_SIZE_4K ; 
 int IWL_CTXT_INFO_RB_SIZE_8K ; 
 int IWL_CTXT_INFO_RB_SIZE_POS ; 
 int IWL_CTXT_INFO_TFD_FORMAT_LONG ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  MQ_RX_TABLE_SIZE ; 
 int RX_QUEUE_CB_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TFD_QUEUE_CB_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UREG_CPU_INIT_RUN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct iwl_context_info* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,struct iwl_context_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_enable_fw_load_int_ctx_info (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_apply_destination (struct iwl_trans*) ; 
 scalar_t__ iwl_pcie_dbg_on (struct iwl_trans*) ; 
 int iwl_pcie_init_fw_sec (struct iwl_trans*,struct fw_img const*,int /*<<< orphan*/ *) ; 
 scalar_t__ iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write64 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 

int iwl_pcie_ctxt_info_init(struct iwl_trans *trans,
			    const struct fw_img *fw)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_context_info *ctxt_info;
	struct iwl_context_info_rbd_cfg *rx_cfg;
	u32 control_flags = 0, rb_size;
	int ret;

	ctxt_info = dma_alloc_coherent(trans->dev, sizeof(*ctxt_info),
				       &trans_pcie->ctxt_info_dma_addr,
				       GFP_KERNEL);
	if (!ctxt_info)
		return -ENOMEM;

	ctxt_info->version.version = 0;
	ctxt_info->version.mac_id =
		cpu_to_le16((u16)iwl_read32(trans, CSR_HW_REV));
	/* size is in DWs */
	ctxt_info->version.size = cpu_to_le16(sizeof(*ctxt_info) / 4);

	switch (trans_pcie->rx_buf_size) {
	case IWL_AMSDU_2K:
		rb_size = IWL_CTXT_INFO_RB_SIZE_2K;
		break;
	case IWL_AMSDU_4K:
		rb_size = IWL_CTXT_INFO_RB_SIZE_4K;
		break;
	case IWL_AMSDU_8K:
		rb_size = IWL_CTXT_INFO_RB_SIZE_8K;
		break;
	case IWL_AMSDU_12K:
		rb_size = IWL_CTXT_INFO_RB_SIZE_12K;
		break;
	default:
		WARN_ON(1);
		rb_size = IWL_CTXT_INFO_RB_SIZE_4K;
	}

	BUILD_BUG_ON(RX_QUEUE_CB_SIZE(MQ_RX_TABLE_SIZE) > 0xF);
	control_flags = IWL_CTXT_INFO_TFD_FORMAT_LONG |
			(RX_QUEUE_CB_SIZE(MQ_RX_TABLE_SIZE) <<
			 IWL_CTXT_INFO_RB_CB_SIZE_POS) |
			(rb_size << IWL_CTXT_INFO_RB_SIZE_POS);
	ctxt_info->control.control_flags = cpu_to_le32(control_flags);

	/* initialize RX default queue */
	rx_cfg = &ctxt_info->rbd_cfg;
	rx_cfg->free_rbd_addr = cpu_to_le64(trans_pcie->rxq->bd_dma);
	rx_cfg->used_rbd_addr = cpu_to_le64(trans_pcie->rxq->used_bd_dma);
	rx_cfg->status_wr_ptr = cpu_to_le64(trans_pcie->rxq->rb_stts_dma);

	/* initialize TX command queue */
	ctxt_info->hcmd_cfg.cmd_queue_addr =
		cpu_to_le64(trans_pcie->txq[trans_pcie->cmd_queue]->dma_addr);
	ctxt_info->hcmd_cfg.cmd_queue_size =
		TFD_QUEUE_CB_SIZE(IWL_CMD_QUEUE_SIZE);

	/* allocate ucode sections in dram and set addresses */
	ret = iwl_pcie_init_fw_sec(trans, fw, &ctxt_info->dram);
	if (ret) {
		dma_free_coherent(trans->dev, sizeof(*trans_pcie->ctxt_info),
				  ctxt_info, trans_pcie->ctxt_info_dma_addr);
		return ret;
	}

	trans_pcie->ctxt_info = ctxt_info;

	iwl_enable_fw_load_int_ctx_info(trans);

	/* Configure debug, if exists */
	if (iwl_pcie_dbg_on(trans))
		iwl_pcie_apply_destination(trans);

	/* kick FW self load */
	iwl_write64(trans, CSR_CTXT_INFO_BA, trans_pcie->ctxt_info_dma_addr);
	iwl_write_prph(trans, UREG_CPU_INIT_RUN, 1);

	/* Context info will be released upon alive or failure to get one */

	return 0;
}