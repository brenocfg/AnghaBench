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
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct TYPE_2__ {scalar_t__ device_family; scalar_t__ mq_rx_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  FH_MEM_RCSR_CHNL0_CONFIG_REG ; 
 int /*<<< orphan*/  FH_MEM_RSSR_RX_STATUS_REG ; 
 int /*<<< orphan*/  FH_RSSR_CHNL0_RX_STATUS_CHNL_IDLE ; 
 scalar_t__ IWL_DEVICE_FAMILY_22560 ; 
 int /*<<< orphan*/  RFH_GEN_STATUS ; 
 int /*<<< orphan*/  RFH_GEN_STATUS_GEN3 ; 
 int /*<<< orphan*/  RFH_RXF_DMA_CFG ; 
 int /*<<< orphan*/  RFH_RXF_DMA_CFG_GEN3 ; 
 int /*<<< orphan*/  RXF_DMA_IDLE ; 
 int iwl_poll_direct_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int iwl_poll_prph_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int iwl_poll_umac_prph_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_umac_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int iwl_pcie_rx_stop(struct iwl_trans *trans)
{
	if (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22560) {
		/* TODO: remove this for 22560 once fw does it */
		iwl_write_umac_prph(trans, RFH_RXF_DMA_CFG_GEN3, 0);
		return iwl_poll_umac_prph_bit(trans, RFH_GEN_STATUS_GEN3,
					      RXF_DMA_IDLE, RXF_DMA_IDLE, 1000);
	} else if (trans->trans_cfg->mq_rx_supported) {
		iwl_write_prph(trans, RFH_RXF_DMA_CFG, 0);
		return iwl_poll_prph_bit(trans, RFH_GEN_STATUS,
					   RXF_DMA_IDLE, RXF_DMA_IDLE, 1000);
	} else {
		iwl_write_direct32(trans, FH_MEM_RCSR_CHNL0_CONFIG_REG, 0);
		return iwl_poll_direct_bit(trans, FH_MEM_RSSR_RX_STATUS_REG,
					   FH_RSSR_CHNL0_RX_STATUS_CHNL_IDLE,
					   1000);
	}
}