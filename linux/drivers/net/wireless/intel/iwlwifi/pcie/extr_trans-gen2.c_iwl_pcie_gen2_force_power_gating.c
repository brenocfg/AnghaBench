#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iwl_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_INIT_DONE ; 
 int /*<<< orphan*/  HPM_HIPM_GEN_CFG ; 
 int HPM_HIPM_GEN_CFG_CR_FORCE_ACTIVE ; 
 int HPM_HIPM_GEN_CFG_CR_PG_EN ; 
 int HPM_HIPM_GEN_CFG_CR_SLP_EN ; 
 int /*<<< orphan*/  iwl_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_clear_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_set_bits_prph (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_trans_sw_reset (struct iwl_trans*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int iwl_pcie_gen2_force_power_gating(struct iwl_trans *trans)
{
	iwl_set_bits_prph(trans, HPM_HIPM_GEN_CFG,
			  HPM_HIPM_GEN_CFG_CR_FORCE_ACTIVE);
	udelay(20);
	iwl_set_bits_prph(trans, HPM_HIPM_GEN_CFG,
			  HPM_HIPM_GEN_CFG_CR_PG_EN |
			  HPM_HIPM_GEN_CFG_CR_SLP_EN);
	udelay(20);
	iwl_clear_bits_prph(trans, HPM_HIPM_GEN_CFG,
			    HPM_HIPM_GEN_CFG_CR_FORCE_ACTIVE);

	iwl_trans_sw_reset(trans);
	iwl_clear_bit(trans, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_INIT_DONE);

	return 0;
}