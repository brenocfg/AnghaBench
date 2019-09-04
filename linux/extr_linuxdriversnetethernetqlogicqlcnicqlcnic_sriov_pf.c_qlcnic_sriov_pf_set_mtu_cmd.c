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
struct qlcnic_vf_info {struct qlcnic_adapter* adapter; } ;
struct TYPE_2__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ rsp; } ;
struct qlcnic_bc_trans {struct qlcnic_vf_info* vf; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int qlcnic_sriov_validate_mtu (struct qlcnic_adapter*,struct qlcnic_vf_info*,struct qlcnic_cmd_args*) ; 

__attribute__((used)) static int qlcnic_sriov_pf_set_mtu_cmd(struct qlcnic_bc_trans *trans,
				       struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_vf_info *vf = trans->vf;
	struct qlcnic_adapter *adapter = vf->adapter;
	int err;

	err = qlcnic_sriov_validate_mtu(adapter, vf, cmd);
	if (err)
		cmd->rsp.arg[0] |= (0x6 << 25);
	else
		err = qlcnic_issue_cmd(adapter, cmd);

	return err;
}