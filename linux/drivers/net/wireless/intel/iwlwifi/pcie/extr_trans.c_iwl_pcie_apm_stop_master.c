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
struct TYPE_4__ {TYPE_1__* csr; } ;
struct TYPE_3__ {int /*<<< orphan*/  flag_master_dis; int /*<<< orphan*/  addr_sw_reset; int /*<<< orphan*/  flag_stop_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_trans*,char*) ; 
 int iwl_poll_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iwl_pcie_apm_stop_master(struct iwl_trans *trans)
{
	int ret;

	/* stop device's busmaster DMA activity */
	iwl_set_bit(trans, trans->trans_cfg->csr->addr_sw_reset,
		    BIT(trans->trans_cfg->csr->flag_stop_master));

	ret = iwl_poll_bit(trans, trans->trans_cfg->csr->addr_sw_reset,
			   BIT(trans->trans_cfg->csr->flag_master_dis),
			   BIT(trans->trans_cfg->csr->flag_master_dis), 100);
	if (ret < 0)
		IWL_WARN(trans, "Master Disable Timed Out, 100 usec\n");

	IWL_DEBUG_INFO(trans, "stop master\n");
}