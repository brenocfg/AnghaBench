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
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_vf_info {int /*<<< orphan*/  vlan_list_lock; int /*<<< orphan*/  sriov_vlans; struct qlcnic_adapter* adapter; } ;
struct qlcnic_sriov {int dummy; } ;
struct qlcnic_adapter {int /*<<< orphan*/  netdev; TYPE_1__* ahw; } ;
typedef  enum qlcnic_vlan_operations { ____Placeholder_qlcnic_vlan_operations } qlcnic_vlan_operations ;
struct TYPE_2__ {struct qlcnic_sriov* sriov; } ;

/* Variables and functions */
#define  QLC_VLAN_ADD 129 
#define  QLC_VLAN_DELETE 128 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qlcnic_sriov_add_vlan_id (struct qlcnic_sriov*,struct qlcnic_vf_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_del_vlan_id (struct qlcnic_sriov*,struct qlcnic_vf_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_sriov_vlan_operation(struct qlcnic_vf_info *vf, u16 vlan_id,
					enum qlcnic_vlan_operations opcode)
{
	struct qlcnic_adapter *adapter = vf->adapter;
	struct qlcnic_sriov *sriov;

	sriov = adapter->ahw->sriov;

	if (!vf->sriov_vlans)
		return;

	spin_lock_bh(&vf->vlan_list_lock);

	switch (opcode) {
	case QLC_VLAN_ADD:
		qlcnic_sriov_add_vlan_id(sriov, vf, vlan_id);
		break;
	case QLC_VLAN_DELETE:
		qlcnic_sriov_del_vlan_id(sriov, vf, vlan_id);
		break;
	default:
		netdev_err(adapter->netdev, "Invalid VLAN operation\n");
	}

	spin_unlock_bh(&vf->vlan_list_lock);
	return;
}