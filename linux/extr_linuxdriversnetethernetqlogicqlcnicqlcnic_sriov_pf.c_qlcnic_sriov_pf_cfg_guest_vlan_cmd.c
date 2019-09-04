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
typedef  int u8 ;
struct qlcnic_vport {scalar_t__ vlan_mode; } ;
struct qlcnic_vf_info {struct qlcnic_vport* vp; struct qlcnic_adapter* adapter; } ;
struct TYPE_4__ {int* arg; } ;
struct TYPE_3__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ rsp; TYPE_1__ req; } ;
struct qlcnic_bc_trans {struct qlcnic_vf_info* vf; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ QLC_GUEST_VLAN_MODE ; 
 int qlcnic_sriov_pf_add_guest_vlan (struct qlcnic_adapter*,struct qlcnic_vf_info*,struct qlcnic_cmd_args*) ; 
 int qlcnic_sriov_pf_del_guest_vlan (struct qlcnic_adapter*,struct qlcnic_vf_info*,struct qlcnic_cmd_args*) ; 

__attribute__((used)) static int qlcnic_sriov_pf_cfg_guest_vlan_cmd(struct qlcnic_bc_trans *tran,
					      struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_vf_info  *vf = tran->vf;
	struct qlcnic_adapter *adapter =  vf->adapter;
	struct qlcnic_vport *vp = vf->vp;
	int err = -EIO;
	u8 op;

	if (vp->vlan_mode != QLC_GUEST_VLAN_MODE) {
		cmd->rsp.arg[0] |= 2 << 25;
		return err;
	}

	op = cmd->req.arg[1] & 0xf;

	if (op)
		err = qlcnic_sriov_pf_add_guest_vlan(adapter, vf, cmd);
	else
		err = qlcnic_sriov_pf_del_guest_vlan(adapter, vf, cmd);

	cmd->rsp.arg[0] |= err ? 2 << 25 : 1 << 25;
	return err;
}