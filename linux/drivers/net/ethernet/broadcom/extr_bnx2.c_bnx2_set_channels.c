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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ethtool_channels {scalar_t__ rx_count; scalar_t__ tx_count; } ;
struct bnx2 {int flags; scalar_t__ num_req_rx_rings; scalar_t__ num_req_tx_rings; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  rx_ring_size; } ;

/* Variables and functions */
 int BNX2_FLAG_MSIX_CAP ; 
 int EINVAL ; 
 scalar_t__ RX_MAX_RINGS ; 
 scalar_t__ TX_MAX_RINGS ; 
 int bnx2_change_ring_size (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  disable_msi ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int bnx2_set_channels(struct net_device *dev,
			      struct ethtool_channels *channels)
{
	struct bnx2 *bp = netdev_priv(dev);
	u32 max_rx_rings = 1;
	u32 max_tx_rings = 1;
	int rc = 0;

	if ((bp->flags & BNX2_FLAG_MSIX_CAP) && !disable_msi) {
		max_rx_rings = RX_MAX_RINGS;
		max_tx_rings = TX_MAX_RINGS;
	}
	if (channels->rx_count > max_rx_rings ||
	    channels->tx_count > max_tx_rings)
		return -EINVAL;

	bp->num_req_rx_rings = channels->rx_count;
	bp->num_req_tx_rings = channels->tx_count;

	if (netif_running(dev))
		rc = bnx2_change_ring_size(bp, bp->rx_ring_size,
					   bp->tx_ring_size, true);

	return rc;
}