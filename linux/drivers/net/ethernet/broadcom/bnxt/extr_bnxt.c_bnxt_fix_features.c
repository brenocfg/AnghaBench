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
struct net_device {int features; } ;
struct TYPE_2__ {scalar_t__ vlan; } ;
struct bnxt {int flags; TYPE_1__ vf; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int BNXT_FLAG_NO_AGG_RINGS ; 
 scalar_t__ BNXT_VF (struct bnxt*) ; 
 int NETIF_F_GRO ; 
 int NETIF_F_GRO_HW ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_STAG_RX ; 
 int NETIF_F_LRO ; 
 int NETIF_F_NTUPLE ; 
 int /*<<< orphan*/  bnxt_rfs_capable (struct bnxt*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_features_t bnxt_fix_features(struct net_device *dev,
					   netdev_features_t features)
{
	struct bnxt *bp = netdev_priv(dev);

	if ((features & NETIF_F_NTUPLE) && !bnxt_rfs_capable(bp))
		features &= ~NETIF_F_NTUPLE;

	if (bp->flags & BNXT_FLAG_NO_AGG_RINGS)
		features &= ~(NETIF_F_LRO | NETIF_F_GRO_HW);

	if (!(features & NETIF_F_GRO))
		features &= ~NETIF_F_GRO_HW;

	if (features & NETIF_F_GRO_HW)
		features &= ~NETIF_F_LRO;

	/* Both CTAG and STAG VLAN accelaration on the RX side have to be
	 * turned on or off together.
	 */
	if ((features & (NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_STAG_RX)) !=
	    (NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_STAG_RX)) {
		if (dev->features & NETIF_F_HW_VLAN_CTAG_RX)
			features &= ~(NETIF_F_HW_VLAN_CTAG_RX |
				      NETIF_F_HW_VLAN_STAG_RX);
		else
			features |= NETIF_F_HW_VLAN_CTAG_RX |
				    NETIF_F_HW_VLAN_STAG_RX;
	}
#ifdef CONFIG_BNXT_SRIOV
	if (BNXT_VF(bp)) {
		if (bp->vf.vlan) {
			features &= ~(NETIF_F_HW_VLAN_CTAG_RX |
				      NETIF_F_HW_VLAN_STAG_RX);
		}
	}
#endif
	return features;
}