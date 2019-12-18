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
struct net_device {int dummy; } ;
struct ice_vsi {TYPE_2__** tx_rings; TYPE_1__** rx_rings; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct ethtool_ringparam {scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; void* tx_max_pending; void* rx_max_pending; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 void* ICE_MAX_NUM_DESC ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
ice_get_ringparam(struct net_device *netdev, struct ethtool_ringparam *ring)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;

	ring->rx_max_pending = ICE_MAX_NUM_DESC;
	ring->tx_max_pending = ICE_MAX_NUM_DESC;
	ring->rx_pending = vsi->rx_rings[0]->count;
	ring->tx_pending = vsi->tx_rings[0]->count;

	/* Rx mini and jumbo rings are not supported */
	ring->rx_mini_max_pending = 0;
	ring->rx_jumbo_max_pending = 0;
	ring->rx_mini_pending = 0;
	ring->rx_jumbo_pending = 0;
}