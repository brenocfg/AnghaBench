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
struct qlcnic_vport {int vlan_mode; int /*<<< orphan*/  pvid; } ;
struct qlcnic_adapter {int /*<<< orphan*/  netdev; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_VLAN_ID ; 
#define  QLC_GUEST_VLAN_MODE 130 
#define  QLC_NO_VLAN_MODE 129 
#define  QLC_PVID_MODE 128 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static __u32 qlcnic_sriov_get_vf_vlan(struct qlcnic_adapter *adapter,
				      struct qlcnic_vport *vp, int vf)
{
	__u32 vlan = 0;

	switch (vp->vlan_mode) {
	case QLC_PVID_MODE:
		vlan = vp->pvid;
		break;
	case QLC_GUEST_VLAN_MODE:
		vlan = MAX_VLAN_ID;
		break;
	case QLC_NO_VLAN_MODE:
		vlan = 0;
		break;
	default:
		netdev_info(adapter->netdev, "Invalid VLAN mode = %d for VF %d\n",
			    vp->vlan_mode, vf);
	}

	return vlan;
}