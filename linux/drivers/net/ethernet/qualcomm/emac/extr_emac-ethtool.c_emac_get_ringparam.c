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
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct emac_adapter {int /*<<< orphan*/  tx_desc_cnt; int /*<<< orphan*/  rx_desc_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_MAX_RX_DESCS ; 
 int /*<<< orphan*/  EMAC_MAX_TX_DESCS ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void emac_get_ringparam(struct net_device *netdev,
			       struct ethtool_ringparam *ring)
{
	struct emac_adapter *adpt = netdev_priv(netdev);

	ring->rx_max_pending = EMAC_MAX_RX_DESCS;
	ring->tx_max_pending = EMAC_MAX_TX_DESCS;
	ring->rx_pending = adpt->rx_desc_cnt;
	ring->tx_pending = adpt->tx_desc_cnt;
}