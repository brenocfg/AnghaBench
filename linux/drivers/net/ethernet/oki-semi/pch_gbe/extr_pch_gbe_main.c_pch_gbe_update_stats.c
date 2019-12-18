#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {scalar_t__ error_state; } ;
struct pch_gbe_hw_stats {scalar_t__ tx_carrier_errors; scalar_t__ tx_aborted_errors; scalar_t__ tx_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; scalar_t__ tx_timeout_count; scalar_t__ tx_length_errors; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  stats_lock; struct pch_gbe_hw_stats stats; struct pci_dev* pdev; struct net_device* netdev; } ;
struct TYPE_2__ {scalar_t__ tx_carrier_errors; scalar_t__ tx_aborted_errors; scalar_t__ tx_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ pci_channel_io_normal ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void pch_gbe_update_stats(struct pch_gbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct pch_gbe_hw_stats *stats = &adapter->stats;
	unsigned long flags;

	/*
	 * Prevent stats update while adapter is being reset, or if the pci
	 * connection is down.
	 */
	if ((pdev->error_state) && (pdev->error_state != pci_channel_io_normal))
		return;

	spin_lock_irqsave(&adapter->stats_lock, flags);

	/* Update device status "adapter->stats" */
	stats->rx_errors = stats->rx_crc_errors + stats->rx_frame_errors;
	stats->tx_errors = stats->tx_length_errors +
	    stats->tx_aborted_errors +
	    stats->tx_carrier_errors + stats->tx_timeout_count;

	/* Update network device status "adapter->net_stats" */
	netdev->stats.rx_packets = stats->rx_packets;
	netdev->stats.rx_bytes = stats->rx_bytes;
	netdev->stats.rx_dropped = stats->rx_dropped;
	netdev->stats.tx_packets = stats->tx_packets;
	netdev->stats.tx_bytes = stats->tx_bytes;
	netdev->stats.tx_dropped = stats->tx_dropped;
	/* Fill out the OS statistics structure */
	netdev->stats.multicast = stats->multicast;
	netdev->stats.collisions = stats->collisions;
	/* Rx Errors */
	netdev->stats.rx_errors = stats->rx_errors;
	netdev->stats.rx_crc_errors = stats->rx_crc_errors;
	netdev->stats.rx_frame_errors = stats->rx_frame_errors;
	/* Tx Errors */
	netdev->stats.tx_errors = stats->tx_errors;
	netdev->stats.tx_aborted_errors = stats->tx_aborted_errors;
	netdev->stats.tx_carrier_errors = stats->tx_carrier_errors;

	spin_unlock_irqrestore(&adapter->stats_lock, flags);
}