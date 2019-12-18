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
typedef  int u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct efx_nic {TYPE_1__* type; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {int (* sriov_set_vf_vlan ) (struct efx_nic*,int,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int VLAN_PRIO_MASK ; 
 int VLAN_PRIO_SHIFT ; 
 int VLAN_VID_MASK ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int stub1 (struct efx_nic*,int,int,int) ; 

int efx_sriov_set_vf_vlan(struct net_device *net_dev, int vf_i, u16 vlan,
			  u8 qos, __be16 vlan_proto)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	if (efx->type->sriov_set_vf_vlan) {
		if ((vlan & ~VLAN_VID_MASK) ||
		    (qos & ~(VLAN_PRIO_MASK >> VLAN_PRIO_SHIFT)))
			return -EINVAL;

		if (vlan_proto != htons(ETH_P_8021Q))
			return -EPROTONOSUPPORT;

		return efx->type->sriov_set_vf_vlan(efx, vf_i, vlan, qos);
	} else {
		return -EOPNOTSUPP;
	}
}