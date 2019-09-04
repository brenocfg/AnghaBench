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
struct ethtool_coalesce {int /*<<< orphan*/  stats_block_coalesce_usecs; int /*<<< orphan*/  tx_max_coalesced_frames_irq; int /*<<< orphan*/  tx_coalesce_usecs_irq; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  rx_max_coalesced_frames_irq; int /*<<< orphan*/  rx_coalesce_usecs_irq; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct bnx2 {int /*<<< orphan*/  stats_ticks; int /*<<< orphan*/  tx_quick_cons_trip_int; int /*<<< orphan*/  tx_ticks_int; int /*<<< orphan*/  tx_quick_cons_trip; int /*<<< orphan*/  tx_ticks; int /*<<< orphan*/  rx_quick_cons_trip_int; int /*<<< orphan*/  rx_ticks_int; int /*<<< orphan*/  rx_quick_cons_trip; int /*<<< orphan*/  rx_ticks; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ethtool_coalesce*,int /*<<< orphan*/ ,int) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
bnx2_get_coalesce(struct net_device *dev, struct ethtool_coalesce *coal)
{
	struct bnx2 *bp = netdev_priv(dev);

	memset(coal, 0, sizeof(struct ethtool_coalesce));

	coal->rx_coalesce_usecs = bp->rx_ticks;
	coal->rx_max_coalesced_frames = bp->rx_quick_cons_trip;
	coal->rx_coalesce_usecs_irq = bp->rx_ticks_int;
	coal->rx_max_coalesced_frames_irq = bp->rx_quick_cons_trip_int;

	coal->tx_coalesce_usecs = bp->tx_ticks;
	coal->tx_max_coalesced_frames = bp->tx_quick_cons_trip;
	coal->tx_coalesce_usecs_irq = bp->tx_ticks_int;
	coal->tx_max_coalesced_frames_irq = bp->tx_quick_cons_trip_int;

	coal->stats_block_coalesce_usecs = bp->stats_ticks;

	return 0;
}