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
struct iwl_trans {TYPE_2__* trans_cfg; } ;
struct TYPE_4__ {TYPE_1__* csr; } ;
struct TYPE_3__ {int /*<<< orphan*/  flag_init_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_PCIDEV_STT_REG ; 
 int /*<<< orphan*/  APMG_PCIDEV_STT_VAL_PERSIST_DIS ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_XTAL_ON ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG_PERSIST_MODE ; 
 int /*<<< orphan*/  CSR_MONITOR_CFG_REG ; 
 int /*<<< orphan*/  CSR_MONITOR_XTAL_RESOURCES ; 
 int SHR_APMG_DL_CFG_DL_CLOCK_POWER_UP ; 
 int /*<<< orphan*/  SHR_APMG_DL_CFG_REG ; 
 int SHR_APMG_GP1_CHICKEN_BIT_SELECT ; 
 int /*<<< orphan*/  SHR_APMG_GP1_REG ; 
 int SHR_APMG_GP1_WF_XTAL_LP_EN ; 
 int /*<<< orphan*/  SHR_APMG_XTAL_CFG_REG ; 
 int SHR_APMG_XTAL_CFG_XTAL_ON_REQ ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __iwl_trans_pcie_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __iwl_trans_pcie_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_clear_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_finish_nic_init (struct iwl_trans*,TYPE_2__*) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_trans_pcie_read_shr (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_pcie_sw_reset (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_trans_pcie_write_shr (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void iwl_pcie_apm_lp_xtal_enable(struct iwl_trans *trans)
{
	int ret;
	u32 apmg_gp1_reg;
	u32 apmg_xtal_cfg_reg;
	u32 dl_cfg_reg;

	/* Force XTAL ON */
	__iwl_trans_pcie_set_bit(trans, CSR_GP_CNTRL,
				 CSR_GP_CNTRL_REG_FLAG_XTAL_ON);

	iwl_trans_pcie_sw_reset(trans);

	ret = iwl_finish_nic_init(trans, trans->trans_cfg);
	if (WARN_ON(ret)) {
		/* Release XTAL ON request */
		__iwl_trans_pcie_clear_bit(trans, CSR_GP_CNTRL,
					   CSR_GP_CNTRL_REG_FLAG_XTAL_ON);
		return;
	}

	/*
	 * Clear "disable persistence" to avoid LP XTAL resetting when
	 * SHRD_HW_RST is applied in S3.
	 */
	iwl_clear_bits_prph(trans, APMG_PCIDEV_STT_REG,
				    APMG_PCIDEV_STT_VAL_PERSIST_DIS);

	/*
	 * Force APMG XTAL to be active to prevent its disabling by HW
	 * caused by APMG idle state.
	 */
	apmg_xtal_cfg_reg = iwl_trans_pcie_read_shr(trans,
						    SHR_APMG_XTAL_CFG_REG);
	iwl_trans_pcie_write_shr(trans, SHR_APMG_XTAL_CFG_REG,
				 apmg_xtal_cfg_reg |
				 SHR_APMG_XTAL_CFG_XTAL_ON_REQ);

	iwl_trans_pcie_sw_reset(trans);

	/* Enable LP XTAL by indirect access through CSR */
	apmg_gp1_reg = iwl_trans_pcie_read_shr(trans, SHR_APMG_GP1_REG);
	iwl_trans_pcie_write_shr(trans, SHR_APMG_GP1_REG, apmg_gp1_reg |
				 SHR_APMG_GP1_WF_XTAL_LP_EN |
				 SHR_APMG_GP1_CHICKEN_BIT_SELECT);

	/* Clear delay line clock power up */
	dl_cfg_reg = iwl_trans_pcie_read_shr(trans, SHR_APMG_DL_CFG_REG);
	iwl_trans_pcie_write_shr(trans, SHR_APMG_DL_CFG_REG, dl_cfg_reg &
				 ~SHR_APMG_DL_CFG_DL_CLOCK_POWER_UP);

	/*
	 * Enable persistence mode to avoid LP XTAL resetting when
	 * SHRD_HW_RST is applied in S3.
	 */
	iwl_set_bit(trans, CSR_HW_IF_CONFIG_REG,
		    CSR_HW_IF_CONFIG_REG_PERSIST_MODE);

	/*
	 * Clear "initialization complete" bit to move adapter from
	 * D0A* (powered-up Active) --> D0U* (Uninitialized) state.
	 */
	iwl_clear_bit(trans, CSR_GP_CNTRL,
		      BIT(trans->trans_cfg->csr->flag_init_done));

	/* Activates XTAL resources monitor */
	__iwl_trans_pcie_set_bit(trans, CSR_MONITOR_CFG_REG,
				 CSR_MONITOR_XTAL_RESOURCES);

	/* Release XTAL ON request */
	__iwl_trans_pcie_clear_bit(trans, CSR_GP_CNTRL,
				   CSR_GP_CNTRL_REG_FLAG_XTAL_ON);
	udelay(10);

	/* Release APMG XTAL */
	iwl_trans_pcie_write_shr(trans, SHR_APMG_XTAL_CFG_REG,
				 apmg_xtal_cfg_reg &
				 ~SHR_APMG_XTAL_CFG_XTAL_ON_REQ);
}