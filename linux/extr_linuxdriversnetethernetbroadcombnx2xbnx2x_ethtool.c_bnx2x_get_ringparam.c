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
struct ethtool_ringparam {int rx_max_pending; int rx_pending; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  tx_max_pending; } ;
struct bnx2x {int rx_ring_size; int /*<<< orphan*/  tx_ring_size; } ;

/* Variables and functions */
 int BNX2X_NUM_RX_QUEUES (struct bnx2x*) ; 
 scalar_t__ IS_MF_FCOE_AFEX (struct bnx2x*) ; 
 int MAX_RX_AVAIL ; 
 int /*<<< orphan*/  MAX_TX_AVAIL ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bnx2x_get_ringparam(struct net_device *dev,
				struct ethtool_ringparam *ering)
{
	struct bnx2x *bp = netdev_priv(dev);

	ering->rx_max_pending = MAX_RX_AVAIL;

	/* If size isn't already set, we give an estimation of the number
	 * of buffers we'll have. We're neglecting some possible conditions
	 * [we couldn't know for certain at this point if number of queues
	 * might shrink] but the number would be correct for the likely
	 * scenario.
	 */
	if (bp->rx_ring_size)
		ering->rx_pending = bp->rx_ring_size;
	else if (BNX2X_NUM_RX_QUEUES(bp))
		ering->rx_pending = MAX_RX_AVAIL / BNX2X_NUM_RX_QUEUES(bp);
	else
		ering->rx_pending = MAX_RX_AVAIL;

	ering->tx_max_pending = IS_MF_FCOE_AFEX(bp) ? 0 : MAX_TX_AVAIL;
	ering->tx_pending = bp->tx_ring_size;
}