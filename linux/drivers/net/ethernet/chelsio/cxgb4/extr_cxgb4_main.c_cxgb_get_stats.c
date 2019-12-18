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
struct rtnl_link_stats64 {scalar_t__ rx_fifo_errors; scalar_t__ rx_length_errors; scalar_t__ rx_errors; int /*<<< orphan*/  tx_errors; scalar_t__ tx_window_errors; scalar_t__ tx_heartbeat_errors; scalar_t__ tx_fifo_errors; scalar_t__ tx_carrier_errors; scalar_t__ tx_aborted_errors; scalar_t__ rx_missed_errors; scalar_t__ rx_dropped; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_over_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct port_stats {scalar_t__ rx_len_err; scalar_t__ rx_fcs_err; scalar_t__ rx_symbol_err; int /*<<< orphan*/  tx_error_frames; scalar_t__ rx_trunc3; scalar_t__ rx_trunc2; scalar_t__ rx_trunc1; scalar_t__ rx_trunc0; scalar_t__ rx_ovflow3; scalar_t__ rx_ovflow2; scalar_t__ rx_ovflow1; scalar_t__ rx_ovflow0; scalar_t__ rx_runt; scalar_t__ rx_too_long; scalar_t__ rx_jabber; int /*<<< orphan*/  rx_mcast_frames; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  rx_octets; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_octets; } ;
struct port_info {int /*<<< orphan*/  stats_base; int /*<<< orphan*/  tx_chan; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct adapter {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_get_port_stats_offset (struct adapter*,int /*<<< orphan*/ ,struct port_stats*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxgb_get_stats(struct net_device *dev,
			   struct rtnl_link_stats64 *ns)
{
	struct port_stats stats;
	struct port_info *p = netdev_priv(dev);
	struct adapter *adapter = p->adapter;

	/* Block retrieving statistics during EEH error
	 * recovery. Otherwise, the recovery might fail
	 * and the PCI device will be removed permanently
	 */
	spin_lock(&adapter->stats_lock);
	if (!netif_device_present(dev)) {
		spin_unlock(&adapter->stats_lock);
		return;
	}
	t4_get_port_stats_offset(adapter, p->tx_chan, &stats,
				 &p->stats_base);
	spin_unlock(&adapter->stats_lock);

	ns->tx_bytes   = stats.tx_octets;
	ns->tx_packets = stats.tx_frames;
	ns->rx_bytes   = stats.rx_octets;
	ns->rx_packets = stats.rx_frames;
	ns->multicast  = stats.rx_mcast_frames;

	/* detailed rx_errors */
	ns->rx_length_errors = stats.rx_jabber + stats.rx_too_long +
			       stats.rx_runt;
	ns->rx_over_errors   = 0;
	ns->rx_crc_errors    = stats.rx_fcs_err;
	ns->rx_frame_errors  = stats.rx_symbol_err;
	ns->rx_dropped	     = stats.rx_ovflow0 + stats.rx_ovflow1 +
			       stats.rx_ovflow2 + stats.rx_ovflow3 +
			       stats.rx_trunc0 + stats.rx_trunc1 +
			       stats.rx_trunc2 + stats.rx_trunc3;
	ns->rx_missed_errors = 0;

	/* detailed tx_errors */
	ns->tx_aborted_errors   = 0;
	ns->tx_carrier_errors   = 0;
	ns->tx_fifo_errors      = 0;
	ns->tx_heartbeat_errors = 0;
	ns->tx_window_errors    = 0;

	ns->tx_errors = stats.tx_error_frames;
	ns->rx_errors = stats.rx_symbol_err + stats.rx_fcs_err +
		ns->rx_length_errors + stats.rx_len_err + ns->rx_fifo_errors;
}