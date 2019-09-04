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
typedef  int /*<<< orphan*/  u16 ;
struct virtchnl_rxq_info {int dma_ring_addr; int hdr_size; int databuffer_size; int max_pkt_size; scalar_t__ splithdr_enabled; int /*<<< orphan*/  ring_len; } ;
struct i40e_vf {struct i40e_pf* pf; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {TYPE_1__* pdev; struct i40e_hw hw; } ;
struct i40e_hmc_obj_rxq {int base; int hsplit_0; int hbuff; int dbuff; int rxmax; int dsize; int lrxqthresh; int crcstrip; int prefena; int l2tsel; int /*<<< orphan*/  dtype; int /*<<< orphan*/  qlen; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int I40E_RXQ_CTX_DBUFF_SHIFT ; 
 int I40E_RXQ_CTX_HBUFF_SHIFT ; 
 int /*<<< orphan*/  I40E_RX_DTYPE_HEADER_SPLIT ; 
 int I40E_RX_SPLIT_IP ; 
 int I40E_RX_SPLIT_L2 ; 
 int I40E_RX_SPLIT_SCTP ; 
 int I40E_RX_SPLIT_TCP_UDP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int i40e_clear_lan_rx_queue_context (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int i40e_set_lan_rx_queue_context (struct i40e_hw*,int /*<<< orphan*/ ,struct i40e_hmc_obj_rxq*) ; 
 int /*<<< orphan*/  i40e_vc_get_pf_queue_id (struct i40e_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct i40e_hmc_obj_rxq*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i40e_config_vsi_rx_queue(struct i40e_vf *vf, u16 vsi_id,
				    u16 vsi_queue_id,
				    struct virtchnl_rxq_info *info)
{
	struct i40e_pf *pf = vf->pf;
	struct i40e_hw *hw = &pf->hw;
	struct i40e_hmc_obj_rxq rx_ctx;
	u16 pf_queue_id;
	int ret = 0;

	pf_queue_id = i40e_vc_get_pf_queue_id(vf, vsi_id, vsi_queue_id);

	/* clear the context structure first */
	memset(&rx_ctx, 0, sizeof(struct i40e_hmc_obj_rxq));

	/* only set the required fields */
	rx_ctx.base = info->dma_ring_addr / 128;
	rx_ctx.qlen = info->ring_len;

	if (info->splithdr_enabled) {
		rx_ctx.hsplit_0 = I40E_RX_SPLIT_L2      |
				  I40E_RX_SPLIT_IP      |
				  I40E_RX_SPLIT_TCP_UDP |
				  I40E_RX_SPLIT_SCTP;
		/* header length validation */
		if (info->hdr_size > ((2 * 1024) - 64)) {
			ret = -EINVAL;
			goto error_param;
		}
		rx_ctx.hbuff = info->hdr_size >> I40E_RXQ_CTX_HBUFF_SHIFT;

		/* set split mode 10b */
		rx_ctx.dtype = I40E_RX_DTYPE_HEADER_SPLIT;
	}

	/* databuffer length validation */
	if (info->databuffer_size > ((16 * 1024) - 128)) {
		ret = -EINVAL;
		goto error_param;
	}
	rx_ctx.dbuff = info->databuffer_size >> I40E_RXQ_CTX_DBUFF_SHIFT;

	/* max pkt. length validation */
	if (info->max_pkt_size >= (16 * 1024) || info->max_pkt_size < 64) {
		ret = -EINVAL;
		goto error_param;
	}
	rx_ctx.rxmax = info->max_pkt_size;

	/* enable 32bytes desc always */
	rx_ctx.dsize = 1;

	/* default values */
	rx_ctx.lrxqthresh = 1;
	rx_ctx.crcstrip = 1;
	rx_ctx.prefena = 1;
	rx_ctx.l2tsel = 1;

	/* clear the context in the HMC */
	ret = i40e_clear_lan_rx_queue_context(hw, pf_queue_id);
	if (ret) {
		dev_err(&pf->pdev->dev,
			"Failed to clear VF LAN Rx queue context %d, error: %d\n",
			pf_queue_id, ret);
		ret = -ENOENT;
		goto error_param;
	}

	/* set the context in the HMC */
	ret = i40e_set_lan_rx_queue_context(hw, pf_queue_id, &rx_ctx);
	if (ret) {
		dev_err(&pf->pdev->dev,
			"Failed to set VF LAN Rx queue context %d error: %d\n",
			pf_queue_id, ret);
		ret = -ENOENT;
		goto error_param;
	}

error_param:
	return ret;
}