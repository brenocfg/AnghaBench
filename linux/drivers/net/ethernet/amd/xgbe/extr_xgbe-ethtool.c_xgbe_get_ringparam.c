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
struct xgbe_prv_data {int /*<<< orphan*/  tx_desc_count; int /*<<< orphan*/  rx_desc_count; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGBE_RX_DESC_CNT_MAX ; 
 int /*<<< orphan*/  XGBE_TX_DESC_CNT_MAX ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xgbe_get_ringparam(struct net_device *netdev,
			       struct ethtool_ringparam *ringparam)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);

	ringparam->rx_max_pending = XGBE_RX_DESC_CNT_MAX;
	ringparam->tx_max_pending = XGBE_TX_DESC_CNT_MAX;
	ringparam->rx_pending = pdata->rx_desc_count;
	ringparam->tx_pending = pdata->tx_desc_count;
}