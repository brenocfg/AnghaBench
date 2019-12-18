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
struct qlcnic_adapter {TYPE_1__* ahw; scalar_t__ need_fw_reset; } ;
struct TYPE_2__ {int /*<<< orphan*/  mailbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_BC_CMD_CHANNEL_INIT ; 
 int /*<<< orphan*/  QLCNIC_BC_CMD_CHANNEL_TERM ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_mbx_interrupt (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_reinit_mbx_work (int /*<<< orphan*/ ) ; 
 int qlcnic_sriov_cfg_bc_intr (struct qlcnic_adapter*,int) ; 
 int qlcnic_sriov_channel_cfg_cmd (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int qlcnic_sriov_vf_init_driver (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_sriov_vf_reinit_driver(struct qlcnic_adapter *adapter)
{
	int err;

	adapter->need_fw_reset = 0;
	qlcnic_83xx_reinit_mbx_work(adapter->ahw->mailbox);
	qlcnic_83xx_enable_mbx_interrupt(adapter);

	err = qlcnic_sriov_cfg_bc_intr(adapter, 1);
	if (err)
		return err;

	err = qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_INIT);
	if (err)
		goto err_out_cleanup_bc_intr;

	err = qlcnic_sriov_vf_init_driver(adapter);
	if (err)
		goto err_out_term_channel;

	return 0;

err_out_term_channel:
	qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_TERM);

err_out_cleanup_bc_intr:
	qlcnic_sriov_cfg_bc_intr(adapter, 0);
	return err;
}