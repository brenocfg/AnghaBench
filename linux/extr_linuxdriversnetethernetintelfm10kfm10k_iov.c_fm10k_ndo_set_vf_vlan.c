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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct fm10k_vf_info {int pf_vid; int /*<<< orphan*/  vsi; } ;
struct fm10k_iov_data {int num_vfs; struct fm10k_vf_info* vf_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_vlan ) (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ mac; } ;
struct fm10k_intfc {struct fm10k_hw hw; struct fm10k_iov_data* iov_data; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  FM10K_VLAN_ALL ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  fm10k_reset_vf_info (struct fm10k_intfc*,struct fm10k_vf_info*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int fm10k_ndo_set_vf_vlan(struct net_device *netdev, int vf_idx, u16 vid,
			  u8 qos, __be16 vlan_proto)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);
	struct fm10k_iov_data *iov_data = interface->iov_data;
	struct fm10k_hw *hw = &interface->hw;
	struct fm10k_vf_info *vf_info;

	/* verify SR-IOV is active and that vf idx is valid */
	if (!iov_data || vf_idx >= iov_data->num_vfs)
		return -EINVAL;

	/* QOS is unsupported and VLAN IDs accepted range 0-4094 */
	if (qos || (vid > (VLAN_VID_MASK - 1)))
		return -EINVAL;

	/* VF VLAN Protocol part to default is unsupported */
	if (vlan_proto != htons(ETH_P_8021Q))
		return -EPROTONOSUPPORT;

	vf_info = &iov_data->vf_info[vf_idx];

	/* exit if there is nothing to do */
	if (vf_info->pf_vid == vid)
		return 0;

	/* record default VLAN ID for VF */
	vf_info->pf_vid = vid;

	/* Clear the VLAN table for the VF */
	hw->mac.ops.update_vlan(hw, FM10K_VLAN_ALL, vf_info->vsi, false);

	fm10k_reset_vf_info(interface, vf_info);

	return 0;
}