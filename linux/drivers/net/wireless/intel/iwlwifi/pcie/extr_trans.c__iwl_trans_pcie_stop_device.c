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
struct iwl_trans_pcie {int is_down; int /*<<< orphan*/  mutex; } ;
struct iwl_trans {int /*<<< orphan*/  status; TYPE_3__* trans_cfg; TYPE_1__* cfg; } ;
struct TYPE_6__ {TYPE_2__* csr; } ;
struct TYPE_5__ {int /*<<< orphan*/  flag_mac_access_req; } ;
struct TYPE_4__ {int /*<<< orphan*/  apmg_not_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_CLK_DIS_REG ; 
 int /*<<< orphan*/  APMG_CLK_VAL_DMA_CLK_RQT ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_DEVICE_ENABLED ; 
 int /*<<< orphan*/  STATUS_INT_ENABLED ; 
 int /*<<< orphan*/  STATUS_SYNC_HCMD_ACTIVE ; 
 int /*<<< orphan*/  STATUS_TPOWER_PMI ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_disable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_enable_rfkill_int (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_apm_stop (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_pcie_conf_msix_hw (struct iwl_trans_pcie*) ; 
 int /*<<< orphan*/  iwl_pcie_disable_ict (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_prepare_card_hw (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_rx_stop (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_tx_stop (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_trans_pcie_sw_reset (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void _iwl_trans_pcie_stop_device(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	lockdep_assert_held(&trans_pcie->mutex);

	if (trans_pcie->is_down)
		return;

	trans_pcie->is_down = true;

	/* tell the device to stop sending interrupts */
	iwl_disable_interrupts(trans);

	/* device going down, Stop using ICT table */
	iwl_pcie_disable_ict(trans);

	/*
	 * If a HW restart happens during firmware loading,
	 * then the firmware loading might call this function
	 * and later it might be called again due to the
	 * restart. So don't process again if the device is
	 * already dead.
	 */
	if (test_and_clear_bit(STATUS_DEVICE_ENABLED, &trans->status)) {
		IWL_DEBUG_INFO(trans,
			       "DEVICE_ENABLED bit was set and is now cleared\n");
		iwl_pcie_tx_stop(trans);
		iwl_pcie_rx_stop(trans);

		/* Power-down device's busmaster DMA clocks */
		if (!trans->cfg->apmg_not_supported) {
			iwl_write_prph(trans, APMG_CLK_DIS_REG,
				       APMG_CLK_VAL_DMA_CLK_RQT);
			udelay(5);
		}
	}

	/* Make sure (redundant) we've released our request to stay awake */
	iwl_clear_bit(trans, CSR_GP_CNTRL,
		      BIT(trans->trans_cfg->csr->flag_mac_access_req));

	/* Stop the device, and put it in low power state */
	iwl_pcie_apm_stop(trans, false);

	iwl_trans_pcie_sw_reset(trans);

	/*
	 * Upon stop, the IVAR table gets erased, so msi-x won't
	 * work. This causes a bug in RF-KILL flows, since the interrupt
	 * that enables radio won't fire on the correct irq, and the
	 * driver won't be able to handle the interrupt.
	 * Configure the IVAR table again after reset.
	 */
	iwl_pcie_conf_msix_hw(trans_pcie);

	/*
	 * Upon stop, the APM issues an interrupt if HW RF kill is set.
	 * This is a bug in certain verions of the hardware.
	 * Certain devices also keep sending HW RF kill interrupt all
	 * the time, unless the interrupt is ACKed even if the interrupt
	 * should be masked. Re-ACK all the interrupts here.
	 */
	iwl_disable_interrupts(trans);

	/* clear all status bits */
	clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
	clear_bit(STATUS_INT_ENABLED, &trans->status);
	clear_bit(STATUS_TPOWER_PMI, &trans->status);

	/*
	 * Even if we stop the HW, we still want the RF kill
	 * interrupt
	 */
	iwl_enable_rfkill_int(trans);

	/* re-take ownership to prevent other users from stealing the device */
	iwl_pcie_prepare_card_hw(trans);
}