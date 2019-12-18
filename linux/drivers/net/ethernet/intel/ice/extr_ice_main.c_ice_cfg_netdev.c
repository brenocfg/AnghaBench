#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int watchdog_timeo; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * perm_addr; int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  ena_tc; } ;
struct ice_vsi {scalar_t__ type; struct net_device* netdev; TYPE_4__ tc_cfg; TYPE_3__* port_info; int /*<<< orphan*/  alloc_rxq; int /*<<< orphan*/  alloc_txq; struct ice_pf* back; } ;
struct ice_pf {TYPE_1__* pdev; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct TYPE_6__ {int /*<<< orphan*/ * perm_addr; } ;
struct TYPE_7__ {TYPE_2__ mac; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int HZ ; 
 int /*<<< orphan*/  ICE_MAX_MTU ; 
 scalar_t__ ICE_VSI_PF ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev_mqs (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_set_netdev_features (struct net_device*) ; 
 int /*<<< orphan*/  ice_set_ops (struct net_device*) ; 
 int /*<<< orphan*/  ice_vsi_cfg_netdev_tc (struct ice_vsi*,int /*<<< orphan*/ ) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int ice_cfg_netdev(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	struct ice_netdev_priv *np;
	struct net_device *netdev;
	u8 mac_addr[ETH_ALEN];
	int err;

	netdev = alloc_etherdev_mqs(sizeof(*np), vsi->alloc_txq,
				    vsi->alloc_rxq);
	if (!netdev)
		return -ENOMEM;

	vsi->netdev = netdev;
	np = netdev_priv(netdev);
	np->vsi = vsi;

	ice_set_netdev_features(netdev);

	ice_set_ops(netdev);

	if (vsi->type == ICE_VSI_PF) {
		SET_NETDEV_DEV(netdev, &pf->pdev->dev);
		ether_addr_copy(mac_addr, vsi->port_info->mac.perm_addr);
		ether_addr_copy(netdev->dev_addr, mac_addr);
		ether_addr_copy(netdev->perm_addr, mac_addr);
	}

	netdev->priv_flags |= IFF_UNICAST_FLT;

	/* Setup netdev TC information */
	ice_vsi_cfg_netdev_tc(vsi, vsi->tc_cfg.ena_tc);

	/* setup watchdog timeout value to be 5 second */
	netdev->watchdog_timeo = 5 * HZ;

	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = ICE_MAX_MTU;

	err = register_netdev(vsi->netdev);
	if (err)
		return err;

	netif_carrier_off(vsi->netdev);

	/* make sure transmit queues start off as stopped */
	netif_tx_stop_all_queues(vsi->netdev);

	return 0;
}