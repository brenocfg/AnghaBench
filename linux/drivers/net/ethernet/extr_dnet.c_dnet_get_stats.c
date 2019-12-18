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
struct net_device_stats {int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; scalar_t__ tx_packets; int /*<<< orphan*/  rx_packets; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_length_errors; int /*<<< orphan*/  tx_errors; scalar_t__ rx_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct dnet_stats {int /*<<< orphan*/  rx_pkt_ignr; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  tx_byte; int /*<<< orphan*/  rx_byte; scalar_t__ tx_brdcast; scalar_t__ tx_multicast; scalar_t__ tx_unicast; int /*<<< orphan*/  rx_ok_pkt; scalar_t__ rx_drib_nib; scalar_t__ rx_pre_shrink; scalar_t__ rx_crc_err; scalar_t__ rx_shrt_frm; scalar_t__ rx_lng_frm; scalar_t__ rx_len_chk_err; int /*<<< orphan*/  tx_bad_fcs; scalar_t__ rx_unsup_opcd; } ;
struct dnet {struct dnet_stats hw_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dnet_print_pretty_hwstats (struct dnet_stats*) ; 
 int /*<<< orphan*/  dnet_update_stats (struct dnet*) ; 
 struct dnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *dnet_get_stats(struct net_device *dev)
{

	struct dnet *bp = netdev_priv(dev);
	struct net_device_stats *nstat = &dev->stats;
	struct dnet_stats *hwstat = &bp->hw_stats;

	/* read stats from hardware */
	dnet_update_stats(bp);

	/* Convert HW stats into netdevice stats */
	nstat->rx_errors = (hwstat->rx_len_chk_err +
			    hwstat->rx_lng_frm + hwstat->rx_shrt_frm +
			    /* ignore IGP violation error
			    hwstat->rx_ipg_viol + */
			    hwstat->rx_crc_err +
			    hwstat->rx_pre_shrink +
			    hwstat->rx_drib_nib + hwstat->rx_unsup_opcd);
	nstat->tx_errors = hwstat->tx_bad_fcs;
	nstat->rx_length_errors = (hwstat->rx_len_chk_err +
				   hwstat->rx_lng_frm +
				   hwstat->rx_shrt_frm + hwstat->rx_pre_shrink);
	nstat->rx_crc_errors = hwstat->rx_crc_err;
	nstat->rx_frame_errors = hwstat->rx_pre_shrink + hwstat->rx_drib_nib;
	nstat->rx_packets = hwstat->rx_ok_pkt;
	nstat->tx_packets = (hwstat->tx_unicast +
			     hwstat->tx_multicast + hwstat->tx_brdcast);
	nstat->rx_bytes = hwstat->rx_byte;
	nstat->tx_bytes = hwstat->tx_byte;
	nstat->multicast = hwstat->rx_multicast;
	nstat->rx_missed_errors = hwstat->rx_pkt_ignr;

	dnet_print_pretty_hwstats(hwstat);

	return nstat;
}