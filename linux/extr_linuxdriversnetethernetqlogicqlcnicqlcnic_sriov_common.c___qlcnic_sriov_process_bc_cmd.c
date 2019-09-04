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
struct TYPE_2__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ rsp; } ;
struct qlcnic_bc_trans {int dummy; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void __qlcnic_sriov_process_bc_cmd(struct qlcnic_adapter *adapter,
					  struct qlcnic_bc_trans *trans,
					  struct qlcnic_cmd_args *cmd)
{
#ifdef CONFIG_QLCNIC_SRIOV
	if (qlcnic_sriov_pf_check(adapter)) {
		qlcnic_sriov_pf_process_bc_cmd(adapter, trans, cmd);
		return;
	}
#endif
	cmd->rsp.arg[0] |= (0x9 << 25);
	return;
}