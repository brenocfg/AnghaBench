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
struct iwl_trans {TYPE_2__* trans_cfg; } ;
struct TYPE_4__ {TYPE_1__* base_params; } ;
struct TYPE_3__ {scalar_t__ shadow_ram_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_PS_CTRL_REG ; 
 int /*<<< orphan*/  APMG_PS_CTRL_VAL_RESET_REQ ; 
 int /*<<< orphan*/  CSR_DBG_LINK_PWR_MGMT_REG ; 
 int /*<<< orphan*/  CSR_RESET_LINK_PWR_MGMT_DISABLED ; 
 int /*<<< orphan*/  iwl_clear_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_finish_nic_init (struct iwl_trans*,TYPE_2__*) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_set_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int iwl_init_otp_access(struct iwl_trans *trans)
{
	int ret;

	ret = iwl_finish_nic_init(trans, trans->trans_cfg);
	if (ret)
		return ret;

	iwl_set_bits_prph(trans, APMG_PS_CTRL_REG,
			  APMG_PS_CTRL_VAL_RESET_REQ);
	udelay(5);
	iwl_clear_bits_prph(trans, APMG_PS_CTRL_REG,
			    APMG_PS_CTRL_VAL_RESET_REQ);

	/*
	 * CSR auto clock gate disable bit -
	 * this is only applicable for HW with OTP shadow RAM
	 */
	if (trans->trans_cfg->base_params->shadow_ram_support)
		iwl_set_bit(trans, CSR_DBG_LINK_PWR_MGMT_REG,
			    CSR_RESET_LINK_PWR_MGMT_DISABLED);

	return 0;
}