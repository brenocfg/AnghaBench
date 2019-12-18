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
struct iwl_trans {int /*<<< orphan*/  status; TYPE_2__* trans_cfg; TYPE_1__* cfg; } ;
struct TYPE_4__ {scalar_t__ device_family; } ;
struct TYPE_3__ {scalar_t__ integrated; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_DBG_HPET_MEM_REG ; 
 int /*<<< orphan*/  CSR_DBG_HPET_MEM_REG_VAL ; 
 int /*<<< orphan*/  CSR_GIO_CHICKEN_BITS ; 
 int /*<<< orphan*/  CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 scalar_t__ IWL_DEVICE_FAMILY_22000 ; 
 int /*<<< orphan*/  STATUS_DEVICE_ENABLED ; 
 int iwl_finish_nic_init (struct iwl_trans*,TYPE_2__*) ; 
 int /*<<< orphan*/  iwl_pcie_apm_config (struct iwl_trans*) ; 
 int iwl_pcie_gen2_force_power_gating (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_pcie_gen2_apm_init(struct iwl_trans *trans)
{
	int ret = 0;

	IWL_DEBUG_INFO(trans, "Init card's basic functions\n");

	/*
	 * Use "set_bit" below rather than "write", to preserve any hardware
	 * bits already set by default after reset.
	 */

	/*
	 * Disable L0s without affecting L1;
	 * don't wait for ICH L0s (ICH bug W/A)
	 */
	iwl_set_bit(trans, CSR_GIO_CHICKEN_BITS,
		    CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX);

	/* Set FH wait threshold to maximum (HW error during stress W/A) */
	iwl_set_bit(trans, CSR_DBG_HPET_MEM_REG, CSR_DBG_HPET_MEM_REG_VAL);

	/*
	 * Enable HAP INTA (interrupt from management bus) to
	 * wake device's PCI Express link L1a -> L0s
	 */
	iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
		    CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A);

	iwl_pcie_apm_config(trans);

	if (trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_22000 &&
	    trans->cfg->integrated) {
		ret = iwl_pcie_gen2_force_power_gating(trans);
		if (ret)
			return ret;
	}

	ret = iwl_finish_nic_init(trans, trans->trans_cfg);
	if (ret)
		return ret;

	set_bit(STATUS_DEVICE_ENABLED, &trans->status);

	return 0;
}