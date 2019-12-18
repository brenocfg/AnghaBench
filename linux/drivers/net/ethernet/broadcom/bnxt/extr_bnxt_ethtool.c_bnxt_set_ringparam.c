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
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; } ;
struct bnxt {scalar_t__ rx_ring_size; scalar_t__ tx_ring_size; } ;

/* Variables and functions */
 scalar_t__ BNXT_MAX_RX_DESC_CNT ; 
 scalar_t__ BNXT_MAX_TX_DESC_CNT ; 
 int EINVAL ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  bnxt_close_nic (struct bnxt*,int,int) ; 
 int bnxt_open_nic (struct bnxt*,int,int) ; 
 int /*<<< orphan*/  bnxt_set_ring_params (struct bnxt*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int bnxt_set_ringparam(struct net_device *dev,
			      struct ethtool_ringparam *ering)
{
	struct bnxt *bp = netdev_priv(dev);

	if ((ering->rx_pending > BNXT_MAX_RX_DESC_CNT) ||
	    (ering->tx_pending > BNXT_MAX_TX_DESC_CNT) ||
	    (ering->tx_pending <= MAX_SKB_FRAGS))
		return -EINVAL;

	if (netif_running(dev))
		bnxt_close_nic(bp, false, false);

	bp->rx_ring_size = ering->rx_pending;
	bp->tx_ring_size = ering->tx_pending;
	bnxt_set_ring_params(bp);

	if (netif_running(dev))
		return bnxt_open_nic(bp, false, false);

	return 0;
}