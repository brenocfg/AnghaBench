#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct net_device_stats {int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_length_errors; scalar_t__ rx_fifo_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; void* rx_missed_errors; void* tx_dropped; void* tx_errors; void* rx_errors; void* rx_packets; scalar_t__ rx_dropped; void* rx_bytes; void* tx_packets; void* tx_bytes; } ;
struct TYPE_12__ {scalar_t__ tx_err_fifo_empty; scalar_t__ tx_err_checksum; void* rx_drop_no_buf; } ;
struct hns_ppe_cb {TYPE_5__ hw_stats; } ;
struct TYPE_14__ {int /*<<< orphan*/  rx_mc_pkts; int /*<<< orphan*/  rx_len_err; scalar_t__ rx_fifo_overrun_err; int /*<<< orphan*/  rx_align_err; int /*<<< orphan*/  rx_fcs_err; scalar_t__ tx_crc_err; scalar_t__ tx_underrun_err; scalar_t__ tx_jabber_err; scalar_t__ tx_fragment_err; scalar_t__ tx_bad_pkts; } ;
struct hns_mac_cb {scalar_t__ mac_type; TYPE_7__ hw_stats; } ;
struct hnae_vf_cb {int port_index; } ;
struct TYPE_10__ {scalar_t__ l3l4_csum_err; scalar_t__ l2_err; scalar_t__ err_pkt_len; scalar_t__ rx_pkts; scalar_t__ rx_bytes; } ;
struct TYPE_11__ {TYPE_3__ stats; } ;
struct TYPE_8__ {scalar_t__ tx_pkts; scalar_t__ tx_bytes; } ;
struct TYPE_9__ {TYPE_1__ stats; } ;
struct hnae_queue {TYPE_4__ rx_ring; TYPE_2__ tx_ring; } ;
struct hnae_handle {int q_num; struct hnae_queue** qs; int /*<<< orphan*/  dev; } ;
struct dsaf_device {TYPE_6__* hw_stats; } ;
struct TYPE_13__ {scalar_t__ stp_drop; scalar_t__ vlan_drop; scalar_t__ rslt_drop; scalar_t__ crc_false; scalar_t__ pad_drop; scalar_t__ bp_drop; } ;

/* Variables and functions */
 int DSAF_PPE_INODE_BASE ; 
 scalar_t__ HNAE_PORT_SERVICE ; 
 struct dsaf_device* hns_ae_get_dsaf_dev (int /*<<< orphan*/ ) ; 
 struct hnae_vf_cb* hns_ae_get_vf_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_dsaf_update_stats (struct dsaf_device*,int) ; 
 struct hns_mac_cb* hns_get_mac_cb (struct hnae_handle*) ; 
 struct hns_ppe_cb* hns_get_ppe_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_mac_update_stats (struct hns_mac_cb*) ; 
 int /*<<< orphan*/  hns_ppe_update_stats (struct hns_ppe_cb*) ; 
 int /*<<< orphan*/  hns_rcb_update_stats (struct hnae_queue*) ; 

__attribute__((used)) static void hns_ae_update_stats(struct hnae_handle *handle,
				struct net_device_stats *net_stats)
{
	int port;
	int idx;
	struct dsaf_device *dsaf_dev;
	struct hns_mac_cb *mac_cb;
	struct hns_ppe_cb *ppe_cb;
	struct hnae_queue *queue;
	struct hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);
	u64 tx_bytes = 0, rx_bytes = 0, tx_packets = 0, rx_packets = 0;
	u64 rx_errors = 0, tx_errors = 0, tx_dropped = 0;
	u64 rx_missed_errors = 0;

	dsaf_dev = hns_ae_get_dsaf_dev(handle->dev);
	if (!dsaf_dev)
		return;
	port = vf_cb->port_index;
	ppe_cb = hns_get_ppe_cb(handle);
	mac_cb = hns_get_mac_cb(handle);

	for (idx = 0; idx < handle->q_num; idx++) {
		queue = handle->qs[idx];
		hns_rcb_update_stats(queue);

		tx_bytes += queue->tx_ring.stats.tx_bytes;
		tx_packets += queue->tx_ring.stats.tx_pkts;
		rx_bytes += queue->rx_ring.stats.rx_bytes;
		rx_packets += queue->rx_ring.stats.rx_pkts;

		rx_errors += queue->rx_ring.stats.err_pkt_len
				+ queue->rx_ring.stats.l2_err
				+ queue->rx_ring.stats.l3l4_csum_err;
	}

	hns_ppe_update_stats(ppe_cb);
	rx_missed_errors = ppe_cb->hw_stats.rx_drop_no_buf;
	tx_errors += ppe_cb->hw_stats.tx_err_checksum
		+ ppe_cb->hw_stats.tx_err_fifo_empty;

	if (mac_cb->mac_type == HNAE_PORT_SERVICE) {
		hns_dsaf_update_stats(dsaf_dev, port);
		/* for port upline direction, i.e., rx. */
		rx_missed_errors += dsaf_dev->hw_stats[port].bp_drop;
		rx_missed_errors += dsaf_dev->hw_stats[port].pad_drop;
		rx_missed_errors += dsaf_dev->hw_stats[port].crc_false;

		/* for port downline direction, i.e., tx. */
		port = port + DSAF_PPE_INODE_BASE;
		hns_dsaf_update_stats(dsaf_dev, port);
		tx_dropped += dsaf_dev->hw_stats[port].bp_drop;
		tx_dropped += dsaf_dev->hw_stats[port].pad_drop;
		tx_dropped += dsaf_dev->hw_stats[port].crc_false;
		tx_dropped += dsaf_dev->hw_stats[port].rslt_drop;
		tx_dropped += dsaf_dev->hw_stats[port].vlan_drop;
		tx_dropped += dsaf_dev->hw_stats[port].stp_drop;
	}

	hns_mac_update_stats(mac_cb);
	rx_errors += mac_cb->hw_stats.rx_fifo_overrun_err;

	tx_errors += mac_cb->hw_stats.tx_bad_pkts
		+ mac_cb->hw_stats.tx_fragment_err
		+ mac_cb->hw_stats.tx_jabber_err
		+ mac_cb->hw_stats.tx_underrun_err
		+ mac_cb->hw_stats.tx_crc_err;

	net_stats->tx_bytes = tx_bytes;
	net_stats->tx_packets = tx_packets;
	net_stats->rx_bytes = rx_bytes;
	net_stats->rx_dropped = 0;
	net_stats->rx_packets = rx_packets;
	net_stats->rx_errors = rx_errors;
	net_stats->tx_errors = tx_errors;
	net_stats->tx_dropped = tx_dropped;
	net_stats->rx_missed_errors = rx_missed_errors;
	net_stats->rx_crc_errors = mac_cb->hw_stats.rx_fcs_err;
	net_stats->rx_frame_errors = mac_cb->hw_stats.rx_align_err;
	net_stats->rx_fifo_errors = mac_cb->hw_stats.rx_fifo_overrun_err;
	net_stats->rx_length_errors = mac_cb->hw_stats.rx_len_err;
	net_stats->multicast = mac_cb->hw_stats.rx_mc_pkts;
}