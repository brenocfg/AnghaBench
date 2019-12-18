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
struct iwl_trans_pcie {int sx_complete; int /*<<< orphan*/  sx_waitq; int /*<<< orphan*/  msix_enabled; } ;
struct iwl_trans {TYPE_2__* trans_cfg; } ;
typedef  enum iwl_d3_status { ____Placeholder_iwl_d3_status } iwl_d3_status ;
struct TYPE_4__ {scalar_t__ device_family; TYPE_1__* csr; } ;
struct TYPE_3__ {int /*<<< orphan*/  flag_mac_access_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_RESET ; 
 int CSR_RESET_REG_FLAG_NEVO_RESET ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int IWL_D3_STATUS_ALIVE ; 
 int IWL_D3_STATUS_RESET ; 
 int /*<<< orphan*/  IWL_DEBUG_POWER (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IWL_DEVICE_FAMILY_AX210 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  UREG_DOORBELL_TO_ISR6 ; 
 int /*<<< orphan*/  UREG_DOORBELL_TO_ISR6_RESUME ; 
 int /*<<< orphan*/  WFPM_GP2 ; 
 int /*<<< orphan*/  iwl_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_enable_interrupts (struct iwl_trans*) ; 
 int iwl_finish_nic_init (struct iwl_trans*,TYPE_2__*) ; 
 int /*<<< orphan*/  iwl_pcie_conf_msix_hw (struct iwl_trans_pcie*) ; 
 int /*<<< orphan*/  iwl_pcie_reset_ict (struct iwl_trans*) ; 
 int iwl_pcie_rx_init (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_set_pwr (struct iwl_trans*,int) ; 
 int iwl_read32 (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_read_umac_prph (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_pcie_tx_reset (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_write_umac_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int iwl_trans_pcie_d3_resume(struct iwl_trans *trans,
				    enum iwl_d3_status *status,
				    bool test,  bool reset)
{
	struct iwl_trans_pcie *trans_pcie =  IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 val;
	int ret;

	if (test) {
		iwl_enable_interrupts(trans);
		*status = IWL_D3_STATUS_ALIVE;
		goto out;
	}

	iwl_set_bit(trans, CSR_GP_CNTRL,
		    BIT(trans->trans_cfg->csr->flag_mac_access_req));

	ret = iwl_finish_nic_init(trans, trans->trans_cfg);
	if (ret)
		return ret;

	/*
	 * Reconfigure IVAR table in case of MSIX or reset ict table in
	 * MSI mode since HW reset erased it.
	 * Also enables interrupts - none will happen as
	 * the device doesn't know we're waking it up, only when
	 * the opmode actually tells it after this call.
	 */
	iwl_pcie_conf_msix_hw(trans_pcie);
	if (!trans_pcie->msix_enabled)
		iwl_pcie_reset_ict(trans);
	iwl_enable_interrupts(trans);

	iwl_pcie_set_pwr(trans, false);

	if (!reset) {
		iwl_clear_bit(trans, CSR_GP_CNTRL,
			      BIT(trans->trans_cfg->csr->flag_mac_access_req));
	} else {
		iwl_trans_pcie_tx_reset(trans);

		ret = iwl_pcie_rx_init(trans);
		if (ret) {
			IWL_ERR(trans,
				"Failed to resume the device (RX reset)\n");
			return ret;
		}
	}

	IWL_DEBUG_POWER(trans, "WFPM value upon resume = 0x%08X\n",
			iwl_read_umac_prph(trans, WFPM_GP2));

	val = iwl_read32(trans, CSR_RESET);
	if (val & CSR_RESET_REG_FLAG_NEVO_RESET)
		*status = IWL_D3_STATUS_RESET;
	else
		*status = IWL_D3_STATUS_ALIVE;

out:
	if (*status == IWL_D3_STATUS_ALIVE &&
	    trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) {
		trans_pcie->sx_complete = false;
		iwl_write_umac_prph(trans, UREG_DOORBELL_TO_ISR6,
				    UREG_DOORBELL_TO_ISR6_RESUME);

		ret = wait_event_timeout(trans_pcie->sx_waitq,
					 trans_pcie->sx_complete, 2 * HZ);
		/*
		 * Invalidate it toward next suspend.
		 */
		trans_pcie->sx_complete = false;

		if (!ret) {
			IWL_ERR(trans, "Timeout exiting D3\n");
			return -ETIMEDOUT;
		}
	}
	return 0;
}