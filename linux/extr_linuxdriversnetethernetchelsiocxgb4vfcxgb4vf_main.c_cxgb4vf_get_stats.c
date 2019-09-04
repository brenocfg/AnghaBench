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
struct t4vf_port_stats {int /*<<< orphan*/  rx_err_frames; int /*<<< orphan*/  tx_drop_frames; scalar_t__ rx_mcast_frames; scalar_t__ rx_ucast_frames; scalar_t__ rx_bcast_frames; scalar_t__ rx_ucast_bytes; scalar_t__ rx_mcast_bytes; scalar_t__ rx_bcast_bytes; scalar_t__ tx_offload_frames; scalar_t__ tx_ucast_frames; scalar_t__ tx_mcast_frames; scalar_t__ tx_bcast_frames; scalar_t__ tx_offload_bytes; scalar_t__ tx_ucast_bytes; scalar_t__ tx_mcast_bytes; scalar_t__ tx_bcast_bytes; } ;
struct port_info {int /*<<< orphan*/  pidx; struct adapter* adapter; } ;
struct net_device_stats {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; scalar_t__ multicast; scalar_t__ rx_packets; scalar_t__ rx_bytes; scalar_t__ tx_packets; scalar_t__ tx_bytes; } ;
struct net_device {struct net_device_stats stats; } ;
struct adapter {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct net_device_stats*,int /*<<< orphan*/ ,int) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int t4vf_get_port_stats (struct adapter*,int /*<<< orphan*/ ,struct t4vf_port_stats*) ; 

__attribute__((used)) static struct net_device_stats *cxgb4vf_get_stats(struct net_device *dev)
{
	struct t4vf_port_stats stats;
	struct port_info *pi = netdev2pinfo(dev);
	struct adapter *adapter = pi->adapter;
	struct net_device_stats *ns = &dev->stats;
	int err;

	spin_lock(&adapter->stats_lock);
	err = t4vf_get_port_stats(adapter, pi->pidx, &stats);
	spin_unlock(&adapter->stats_lock);

	memset(ns, 0, sizeof(*ns));
	if (err)
		return ns;

	ns->tx_bytes = (stats.tx_bcast_bytes + stats.tx_mcast_bytes +
			stats.tx_ucast_bytes + stats.tx_offload_bytes);
	ns->tx_packets = (stats.tx_bcast_frames + stats.tx_mcast_frames +
			  stats.tx_ucast_frames + stats.tx_offload_frames);
	ns->rx_bytes = (stats.rx_bcast_bytes + stats.rx_mcast_bytes +
			stats.rx_ucast_bytes);
	ns->rx_packets = (stats.rx_bcast_frames + stats.rx_mcast_frames +
			  stats.rx_ucast_frames);
	ns->multicast = stats.rx_mcast_frames;
	ns->tx_errors = stats.tx_drop_frames;
	ns->rx_errors = stats.rx_err_frames;

	return ns;
}