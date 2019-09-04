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
typedef  int u16 ;
struct qlcnic_vf_info {int /*<<< orphan*/  rx_ctx_id; } ;
struct qlcnic_sriov {int dummy; } ;
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ req; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_3__ {struct qlcnic_sriov* sriov; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QLCNIC_MAC_ADD ; 
 int /*<<< orphan*/  QLCNIC_MAC_DEL ; 
 scalar_t__ qlcnic_83xx_pf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_cfg_vf_def_mac (struct qlcnic_adapter*,struct qlcnic_vf_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_check_any_vlan (struct qlcnic_vf_info*) ; 
 int /*<<< orphan*/  qlcnic_sriov_del_vlan_id (struct qlcnic_sriov*,struct qlcnic_vf_info*,int) ; 

__attribute__((used)) static int qlcnic_sriov_pf_del_guest_vlan(struct qlcnic_adapter *adapter,
					  struct qlcnic_vf_info *vf,
					  struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_sriov *sriov = adapter->ahw->sriov;
	u16 vlan;

	if (!qlcnic_sriov_check_any_vlan(vf))
		return -EINVAL;

	vlan = cmd->req.arg[1] >> 16;
	if (!vf->rx_ctx_id) {
		qlcnic_sriov_del_vlan_id(sriov, vf, vlan);
		return 0;
	}

	qlcnic_sriov_cfg_vf_def_mac(adapter, vf, vlan, QLCNIC_MAC_DEL);
	qlcnic_sriov_del_vlan_id(sriov, vf, vlan);

	if (qlcnic_83xx_pf_check(adapter))
		qlcnic_sriov_cfg_vf_def_mac(adapter, vf,
					    0, QLCNIC_MAC_ADD);
	return 0;
}