#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct iwl_op_mode {int dummy; } ;
struct iwl_mvm {TYPE_3__* trans; int /*<<< orphan*/  fwrt; } ;
struct TYPE_7__ {TYPE_2__* cfg; TYPE_1__* trans_cfg; int /*<<< orphan*/  hw_rev; } ;
struct TYPE_6__ {int /*<<< orphan*/  apmg_not_supported; } ;
struct TYPE_5__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS ; 
 int /*<<< orphan*/  APMG_PS_CTRL_REG ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int CSR_HW_IF_CONFIG_REG_BIT_MAC_SI ; 
 int CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI ; 
 int CSR_HW_IF_CONFIG_REG_D3_DEBUG ; 
 int CSR_HW_IF_CONFIG_REG_MSK_MAC_DASH ; 
 int CSR_HW_IF_CONFIG_REG_MSK_MAC_STEP ; 
 int CSR_HW_IF_CONFIG_REG_MSK_PHY_DASH ; 
 int CSR_HW_IF_CONFIG_REG_MSK_PHY_STEP ; 
 int CSR_HW_IF_CONFIG_REG_MSK_PHY_TYPE ; 
 int CSR_HW_IF_CONFIG_REG_POS_MAC_DASH ; 
 int CSR_HW_IF_CONFIG_REG_POS_MAC_STEP ; 
 int CSR_HW_IF_CONFIG_REG_POS_PHY_DASH ; 
 int CSR_HW_IF_CONFIG_REG_POS_PHY_STEP ; 
 int CSR_HW_IF_CONFIG_REG_POS_PHY_TYPE ; 
 int CSR_HW_REV_DASH (int /*<<< orphan*/ ) ; 
 int CSR_HW_REV_STEP (int /*<<< orphan*/ ) ; 
 int FW_PHY_CFG_RADIO_DASH ; 
 int FW_PHY_CFG_RADIO_DASH_POS ; 
 int FW_PHY_CFG_RADIO_STEP ; 
 int FW_PHY_CFG_RADIO_STEP_POS ; 
 int FW_PHY_CFG_RADIO_TYPE ; 
 int FW_PHY_CFG_RADIO_TYPE_POS ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_mvm*,char*,int,int,int) ; 
 scalar_t__ IWL_DEVICE_FAMILY_8000 ; 
 struct iwl_mvm* IWL_OP_MODE_GET_MVM (struct iwl_op_mode*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ iwl_fw_dbg_is_d3_debug_enabled (int /*<<< orphan*/ *) ; 
 int iwl_mvm_get_phy_config (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_set_bits_mask_prph (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_set_bits_mask (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void iwl_mvm_nic_config(struct iwl_op_mode *op_mode)
{
	struct iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	u8 radio_cfg_type, radio_cfg_step, radio_cfg_dash;
	u32 reg_val = 0;
	u32 phy_config = iwl_mvm_get_phy_config(mvm);

	radio_cfg_type = (phy_config & FW_PHY_CFG_RADIO_TYPE) >>
			 FW_PHY_CFG_RADIO_TYPE_POS;
	radio_cfg_step = (phy_config & FW_PHY_CFG_RADIO_STEP) >>
			 FW_PHY_CFG_RADIO_STEP_POS;
	radio_cfg_dash = (phy_config & FW_PHY_CFG_RADIO_DASH) >>
			 FW_PHY_CFG_RADIO_DASH_POS;

	/* SKU control */
	reg_val |= CSR_HW_REV_STEP(mvm->trans->hw_rev) <<
				CSR_HW_IF_CONFIG_REG_POS_MAC_STEP;
	reg_val |= CSR_HW_REV_DASH(mvm->trans->hw_rev) <<
				CSR_HW_IF_CONFIG_REG_POS_MAC_DASH;

	/* radio configuration */
	reg_val |= radio_cfg_type << CSR_HW_IF_CONFIG_REG_POS_PHY_TYPE;
	reg_val |= radio_cfg_step << CSR_HW_IF_CONFIG_REG_POS_PHY_STEP;
	reg_val |= radio_cfg_dash << CSR_HW_IF_CONFIG_REG_POS_PHY_DASH;

	WARN_ON((radio_cfg_type << CSR_HW_IF_CONFIG_REG_POS_PHY_TYPE) &
		 ~CSR_HW_IF_CONFIG_REG_MSK_PHY_TYPE);

	/*
	 * TODO: Bits 7-8 of CSR in 8000 HW family and higher set the ADC
	 * sampling, and shouldn't be set to any non-zero value.
	 * The same is supposed to be true of the other HW, but unsetting
	 * them (such as the 7260) causes automatic tests to fail on seemingly
	 * unrelated errors. Need to further investigate this, but for now
	 * we'll separate cases.
	 */
	if (mvm->trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_8000)
		reg_val |= CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI;

	if (iwl_fw_dbg_is_d3_debug_enabled(&mvm->fwrt))
		reg_val |= CSR_HW_IF_CONFIG_REG_D3_DEBUG;

	iwl_trans_set_bits_mask(mvm->trans, CSR_HW_IF_CONFIG_REG,
				CSR_HW_IF_CONFIG_REG_MSK_MAC_DASH |
				CSR_HW_IF_CONFIG_REG_MSK_MAC_STEP |
				CSR_HW_IF_CONFIG_REG_MSK_PHY_TYPE |
				CSR_HW_IF_CONFIG_REG_MSK_PHY_STEP |
				CSR_HW_IF_CONFIG_REG_MSK_PHY_DASH |
				CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI |
				CSR_HW_IF_CONFIG_REG_BIT_MAC_SI   |
				CSR_HW_IF_CONFIG_REG_D3_DEBUG,
				reg_val);

	IWL_DEBUG_INFO(mvm, "Radio type=0x%x-0x%x-0x%x\n", radio_cfg_type,
		       radio_cfg_step, radio_cfg_dash);

	/*
	 * W/A : NIC is stuck in a reset state after Early PCIe power off
	 * (PCIe power is lost before PERST# is asserted), causing ME FW
	 * to lose ownership and not being able to obtain it back.
	 */
	if (!mvm->trans->cfg->apmg_not_supported)
		iwl_set_bits_mask_prph(mvm->trans, APMG_PS_CTRL_REG,
				       APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS,
				       ~APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS);
}