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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct virtchnl_txq_info {int dma_ring_addr; int /*<<< orphan*/  dma_headwb_addr; int /*<<< orphan*/  headwb_enabled; int /*<<< orphan*/  ring_len; int /*<<< orphan*/  vsi_id; } ;
struct TYPE_4__ {int /*<<< orphan*/ * qs_handle; } ;
struct i40e_vsi {TYPE_1__ info; } ;
struct i40e_vf {int vf_id; struct i40e_pf* pf; } ;
struct TYPE_6__ {int vf_base_id; } ;
struct i40e_hw {int pf_id; TYPE_3__ func_caps; } ;
struct i40e_pf {TYPE_2__* pdev; struct i40e_hw hw; } ;
struct i40e_hmc_obj_txq {int base; int /*<<< orphan*/  head_wb_addr; int /*<<< orphan*/  head_wb_ena; scalar_t__ rdylist_act; int /*<<< orphan*/  rdylist; int /*<<< orphan*/  qlen; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  I40E_QTX_CTL (int /*<<< orphan*/ ) ; 
 int I40E_QTX_CTL_PF_INDX_MASK ; 
 int I40E_QTX_CTL_PF_INDX_SHIFT ; 
 int I40E_QTX_CTL_VFVM_INDX_MASK ; 
 int I40E_QTX_CTL_VFVM_INDX_SHIFT ; 
 int I40E_QTX_CTL_VF_QUEUE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int i40e_clear_lan_tx_queue_context (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 struct i40e_vsi* i40e_find_vsi_from_id (struct i40e_pf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int i40e_set_lan_tx_queue_context (struct i40e_hw*,int /*<<< orphan*/ ,struct i40e_hmc_obj_txq*) ; 
 int /*<<< orphan*/  i40e_vc_get_pf_queue_id (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_vc_isvalid_vsi_id (struct i40e_vf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct i40e_hmc_obj_txq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i40e_config_vsi_tx_queue(struct i40e_vf *vf, u16 vsi_id,
				    u16 vsi_queue_id,
				    struct virtchnl_txq_info *info)
{
	struct i40e_pf *pf = vf->pf;
	struct i40e_hw *hw = &pf->hw;
	struct i40e_hmc_obj_txq tx_ctx;
	struct i40e_vsi *vsi;
	u16 pf_queue_id;
	u32 qtx_ctl;
	int ret = 0;

	if (!i40e_vc_isvalid_vsi_id(vf, info->vsi_id)) {
		ret = -ENOENT;
		goto error_context;
	}
	pf_queue_id = i40e_vc_get_pf_queue_id(vf, vsi_id, vsi_queue_id);
	vsi = i40e_find_vsi_from_id(pf, vsi_id);
	if (!vsi) {
		ret = -ENOENT;
		goto error_context;
	}

	/* clear the context structure first */
	memset(&tx_ctx, 0, sizeof(struct i40e_hmc_obj_txq));

	/* only set the required fields */
	tx_ctx.base = info->dma_ring_addr / 128;
	tx_ctx.qlen = info->ring_len;
	tx_ctx.rdylist = le16_to_cpu(vsi->info.qs_handle[0]);
	tx_ctx.rdylist_act = 0;
	tx_ctx.head_wb_ena = info->headwb_enabled;
	tx_ctx.head_wb_addr = info->dma_headwb_addr;

	/* clear the context in the HMC */
	ret = i40e_clear_lan_tx_queue_context(hw, pf_queue_id);
	if (ret) {
		dev_err(&pf->pdev->dev,
			"Failed to clear VF LAN Tx queue context %d, error: %d\n",
			pf_queue_id, ret);
		ret = -ENOENT;
		goto error_context;
	}

	/* set the context in the HMC */
	ret = i40e_set_lan_tx_queue_context(hw, pf_queue_id, &tx_ctx);
	if (ret) {
		dev_err(&pf->pdev->dev,
			"Failed to set VF LAN Tx queue context %d error: %d\n",
			pf_queue_id, ret);
		ret = -ENOENT;
		goto error_context;
	}

	/* associate this queue with the PCI VF function */
	qtx_ctl = I40E_QTX_CTL_VF_QUEUE;
	qtx_ctl |= ((hw->pf_id << I40E_QTX_CTL_PF_INDX_SHIFT)
		    & I40E_QTX_CTL_PF_INDX_MASK);
	qtx_ctl |= (((vf->vf_id + hw->func_caps.vf_base_id)
		     << I40E_QTX_CTL_VFVM_INDX_SHIFT)
		    & I40E_QTX_CTL_VFVM_INDX_MASK);
	wr32(hw, I40E_QTX_CTL(pf_queue_id), qtx_ctl);
	i40e_flush(hw);

error_context:
	return ret;
}