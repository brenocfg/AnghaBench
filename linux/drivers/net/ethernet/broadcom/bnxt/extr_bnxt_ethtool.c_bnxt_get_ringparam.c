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
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_jumbo_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_jumbo_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct bnxt {int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  rx_agg_ring_size; int /*<<< orphan*/  rx_ring_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_MAX_RX_DESC_CNT ; 
 int /*<<< orphan*/  BNXT_MAX_RX_JUM_DESC_CNT ; 
 int /*<<< orphan*/  BNXT_MAX_TX_DESC_CNT ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bnxt_get_ringparam(struct net_device *dev,
			       struct ethtool_ringparam *ering)
{
	struct bnxt *bp = netdev_priv(dev);

	ering->rx_max_pending = BNXT_MAX_RX_DESC_CNT;
	ering->rx_jumbo_max_pending = BNXT_MAX_RX_JUM_DESC_CNT;
	ering->tx_max_pending = BNXT_MAX_TX_DESC_CNT;

	ering->rx_pending = bp->rx_ring_size;
	ering->rx_jumbo_pending = bp->rx_agg_ring_size;
	ering->tx_pending = bp->tx_ring_size;
}