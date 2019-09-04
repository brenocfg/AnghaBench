#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_vf_info {scalar_t__ rx_ctx_id; TYPE_3__* vp; struct qlcnic_adapter* adapter; } ;
struct TYPE_5__ {int* arg; } ;
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ req; TYPE_1__ rsp; } ;
struct qlcnic_bc_trans {struct qlcnic_vf_info* vf; } ;
struct qlcnic_adapter {int dummy; } ;
struct TYPE_6__ {int handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_MAC_DEL ; 
 int /*<<< orphan*/  qlcnic_83xx_cfg_default_mac_vlan (struct qlcnic_adapter*,struct qlcnic_vf_info*,int /*<<< orphan*/ ) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int qlcnic_sriov_validate_del_rx_ctx (struct qlcnic_vf_info*,struct qlcnic_cmd_args*) ; 

__attribute__((used)) static int qlcnic_sriov_pf_del_rx_ctx_cmd(struct qlcnic_bc_trans *trans,
					  struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_vf_info *vf = trans->vf;
	struct qlcnic_adapter *adapter = vf->adapter;
	int err;

	err = qlcnic_sriov_validate_del_rx_ctx(vf, cmd);
	if (err) {
		cmd->rsp.arg[0] |= (0x6 << 25);
		return err;
	}

	qlcnic_83xx_cfg_default_mac_vlan(adapter, vf, QLCNIC_MAC_DEL);
	cmd->req.arg[1] |= vf->vp->handle << 16;
	err = qlcnic_issue_cmd(adapter, cmd);

	if (!err)
		vf->rx_ctx_id = 0;

	return err;
}