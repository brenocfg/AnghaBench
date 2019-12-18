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
struct iwl_trans {TYPE_3__* trans_cfg; int /*<<< orphan*/  status; } ;
struct iwl_rxq {int need_update; int write_actual; int id; int /*<<< orphan*/  write; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {scalar_t__ device_family; scalar_t__ mq_rx_supported; TYPE_2__* csr; TYPE_1__* base_params; } ;
struct TYPE_5__ {int /*<<< orphan*/  flag_mac_access_req; } ;
struct TYPE_4__ {int /*<<< orphan*/  shadow_reg_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1 ; 
 int CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP ; 
 int /*<<< orphan*/  FH_RSCSR_CHNL0_WPTR ; 
 int FIRST_RX_QUEUE ; 
 int /*<<< orphan*/  HBUS_TARG_WRPTR ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*,int) ; 
 scalar_t__ IWL_DEVICE_FAMILY_22560 ; 
 int /*<<< orphan*/  RFH_Q_FRBDCB_WIDX_TRG (int) ; 
 int /*<<< orphan*/  STATUS_TPOWER_PMI ; 
 int iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int round_down (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_pcie_rxq_inc_wr_ptr(struct iwl_trans *trans,
				    struct iwl_rxq *rxq)
{
	u32 reg;

	lockdep_assert_held(&rxq->lock);

	/*
	 * explicitly wake up the NIC if:
	 * 1. shadow registers aren't enabled
	 * 2. there is a chance that the NIC is asleep
	 */
	if (!trans->trans_cfg->base_params->shadow_reg_enable &&
	    test_bit(STATUS_TPOWER_PMI, &trans->status)) {
		reg = iwl_read32(trans, CSR_UCODE_DRV_GP1);

		if (reg & CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP) {
			IWL_DEBUG_INFO(trans, "Rx queue requesting wakeup, GP1 = 0x%x\n",
				       reg);
			iwl_set_bit(trans, CSR_GP_CNTRL,
				    BIT(trans->trans_cfg->csr->flag_mac_access_req));
			rxq->need_update = true;
			return;
		}
	}

	rxq->write_actual = round_down(rxq->write, 8);
	if (trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_22560)
		iwl_write32(trans, HBUS_TARG_WRPTR,
			    (rxq->write_actual |
			     ((FIRST_RX_QUEUE + rxq->id) << 16)));
	else if (trans->trans_cfg->mq_rx_supported)
		iwl_write32(trans, RFH_Q_FRBDCB_WIDX_TRG(rxq->id),
			    rxq->write_actual);
	else
		iwl_write32(trans, FH_RSCSR_CHNL0_WPTR, rxq->write_actual);
}