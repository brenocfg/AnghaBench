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
struct net_device_stats {scalar_t__ tx_fifo_errors; scalar_t__ tx_carrier_errors; scalar_t__ tx_aborted_errors; scalar_t__ rx_fifo_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_over_errors; scalar_t__ rx_length_errors; scalar_t__ collisions; scalar_t__ tx_errors; scalar_t__ rx_errors; } ;
struct net_device {int dummy; } ;
struct macb_stats {scalar_t__ tx_underruns; scalar_t__ tx_carrier_errors; scalar_t__ tx_excessive_cols; scalar_t__ rx_overruns; scalar_t__ rx_align_errors; scalar_t__ rx_fcs_errors; scalar_t__ rx_resource_errors; scalar_t__ rx_length_mismatch; scalar_t__ rx_undersize_pkts; scalar_t__ rx_jabbers; scalar_t__ rx_oversize_pkts; scalar_t__ tx_multiple_cols; scalar_t__ tx_single_cols; scalar_t__ sqe_test_errors; scalar_t__ tx_late_cols; } ;
struct TYPE_4__ {struct macb_stats macb; } ;
struct macb {TYPE_2__ hw_stats; TYPE_1__* dev; } ;
struct TYPE_3__ {struct net_device_stats stats; } ;

/* Variables and functions */
 struct net_device_stats* gem_get_stats (struct macb*) ; 
 scalar_t__ macb_is_gem (struct macb*) ; 
 int /*<<< orphan*/  macb_update_stats (struct macb*) ; 
 struct macb* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *macb_get_stats(struct net_device *dev)
{
	struct macb *bp = netdev_priv(dev);
	struct net_device_stats *nstat = &bp->dev->stats;
	struct macb_stats *hwstat = &bp->hw_stats.macb;

	if (macb_is_gem(bp))
		return gem_get_stats(bp);

	/* read stats from hardware */
	macb_update_stats(bp);

	/* Convert HW stats into netdevice stats */
	nstat->rx_errors = (hwstat->rx_fcs_errors +
			    hwstat->rx_align_errors +
			    hwstat->rx_resource_errors +
			    hwstat->rx_overruns +
			    hwstat->rx_oversize_pkts +
			    hwstat->rx_jabbers +
			    hwstat->rx_undersize_pkts +
			    hwstat->rx_length_mismatch);
	nstat->tx_errors = (hwstat->tx_late_cols +
			    hwstat->tx_excessive_cols +
			    hwstat->tx_underruns +
			    hwstat->tx_carrier_errors +
			    hwstat->sqe_test_errors);
	nstat->collisions = (hwstat->tx_single_cols +
			     hwstat->tx_multiple_cols +
			     hwstat->tx_excessive_cols);
	nstat->rx_length_errors = (hwstat->rx_oversize_pkts +
				   hwstat->rx_jabbers +
				   hwstat->rx_undersize_pkts +
				   hwstat->rx_length_mismatch);
	nstat->rx_over_errors = hwstat->rx_resource_errors +
				   hwstat->rx_overruns;
	nstat->rx_crc_errors = hwstat->rx_fcs_errors;
	nstat->rx_frame_errors = hwstat->rx_align_errors;
	nstat->rx_fifo_errors = hwstat->rx_overruns;
	/* XXX: What does "missed" mean? */
	nstat->tx_aborted_errors = hwstat->tx_excessive_cols;
	nstat->tx_carrier_errors = hwstat->tx_carrier_errors;
	nstat->tx_fifo_errors = hwstat->tx_underruns;
	/* Don't know about heartbeat or window errors... */

	return nstat;
}