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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_carrier_errors; scalar_t__ tx_window_errors; scalar_t__ tx_aborted_errors; scalar_t__ tx_errors; int /*<<< orphan*/  rx_missed_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_length_errors; scalar_t__ rx_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tncrs; scalar_t__ latecol; scalar_t__ ecol; int /*<<< orphan*/  mpc; scalar_t__ algnerrc; scalar_t__ crcerrs; scalar_t__ roc; scalar_t__ ruc; scalar_t__ cexterr; scalar_t__ rxerrc; int /*<<< orphan*/  colc; int /*<<< orphan*/  mprc; int /*<<< orphan*/  gptc; int /*<<< orphan*/  gotc; int /*<<< orphan*/  gprc; int /*<<< orphan*/  gorc; } ;
struct e1000_adapter {int /*<<< orphan*/  stats64_lock; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000e_update_stats (struct e1000_adapter*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void e1000e_get_stats64(struct net_device *netdev,
			struct rtnl_link_stats64 *stats)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);

	spin_lock(&adapter->stats64_lock);
	e1000e_update_stats(adapter);
	/* Fill out the OS statistics structure */
	stats->rx_bytes = adapter->stats.gorc;
	stats->rx_packets = adapter->stats.gprc;
	stats->tx_bytes = adapter->stats.gotc;
	stats->tx_packets = adapter->stats.gptc;
	stats->multicast = adapter->stats.mprc;
	stats->collisions = adapter->stats.colc;

	/* Rx Errors */

	/* RLEC on some newer hardware can be incorrect so build
	 * our own version based on RUC and ROC
	 */
	stats->rx_errors = adapter->stats.rxerrc +
	    adapter->stats.crcerrs + adapter->stats.algnerrc +
	    adapter->stats.ruc + adapter->stats.roc + adapter->stats.cexterr;
	stats->rx_length_errors = adapter->stats.ruc + adapter->stats.roc;
	stats->rx_crc_errors = adapter->stats.crcerrs;
	stats->rx_frame_errors = adapter->stats.algnerrc;
	stats->rx_missed_errors = adapter->stats.mpc;

	/* Tx Errors */
	stats->tx_errors = adapter->stats.ecol + adapter->stats.latecol;
	stats->tx_aborted_errors = adapter->stats.ecol;
	stats->tx_window_errors = adapter->stats.latecol;
	stats->tx_carrier_errors = adapter->stats.tncrs;

	/* Tx Dropped needs to be maintained elsewhere */

	spin_unlock(&adapter->stats64_lock);
}