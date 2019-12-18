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
struct ravb_private {scalar_t__ chip_id; struct net_device_stats* stats; } ;
struct net_device_stats {scalar_t__ rx_over_errors; scalar_t__ rx_missed_errors; scalar_t__ rx_length_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_errors; scalar_t__ multicast; scalar_t__ tx_bytes; scalar_t__ rx_bytes; scalar_t__ tx_packets; scalar_t__ rx_packets; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 size_t RAVB_BE ; 
 size_t RAVB_NC ; 
 scalar_t__ RCAR_GEN3 ; 
 int /*<<< orphan*/  TROCR ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 scalar_t__ ravb_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device_stats *ravb_get_stats(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	struct net_device_stats *nstats, *stats0, *stats1;

	nstats = &ndev->stats;
	stats0 = &priv->stats[RAVB_BE];
	stats1 = &priv->stats[RAVB_NC];

	if (priv->chip_id == RCAR_GEN3) {
		nstats->tx_dropped += ravb_read(ndev, TROCR);
		ravb_write(ndev, 0, TROCR);	/* (write clear) */
	}

	nstats->rx_packets = stats0->rx_packets + stats1->rx_packets;
	nstats->tx_packets = stats0->tx_packets + stats1->tx_packets;
	nstats->rx_bytes = stats0->rx_bytes + stats1->rx_bytes;
	nstats->tx_bytes = stats0->tx_bytes + stats1->tx_bytes;
	nstats->multicast = stats0->multicast + stats1->multicast;
	nstats->rx_errors = stats0->rx_errors + stats1->rx_errors;
	nstats->rx_crc_errors = stats0->rx_crc_errors + stats1->rx_crc_errors;
	nstats->rx_frame_errors =
		stats0->rx_frame_errors + stats1->rx_frame_errors;
	nstats->rx_length_errors =
		stats0->rx_length_errors + stats1->rx_length_errors;
	nstats->rx_missed_errors =
		stats0->rx_missed_errors + stats1->rx_missed_errors;
	nstats->rx_over_errors =
		stats0->rx_over_errors + stats1->rx_over_errors;

	return nstats;
}