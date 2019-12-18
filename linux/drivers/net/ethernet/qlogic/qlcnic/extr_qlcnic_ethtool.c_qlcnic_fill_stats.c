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
typedef  int /*<<< orphan*/  u64 ;
struct qlcnic_mac_statistics {int /*<<< orphan*/  mac_align_error; int /*<<< orphan*/  mac_rx_crc_error; int /*<<< orphan*/  mac_rx_dropped; int /*<<< orphan*/  mac_rx_jabber; int /*<<< orphan*/  mac_rx_length_large; int /*<<< orphan*/  mac_rx_length_small; int /*<<< orphan*/  mac_rx_length_error; int /*<<< orphan*/  mac_rx_gt_1518b_pkts; int /*<<< orphan*/  mac_rx_lt_1518b_pkts; int /*<<< orphan*/  mac_rx_lt_1023b_pkts; int /*<<< orphan*/  mac_rx_lt_511b_pkts; int /*<<< orphan*/  mac_rx_lt_255b_pkts; int /*<<< orphan*/  mac_rx_lt_127b_pkts; int /*<<< orphan*/  mac_rx_lt_64b_pkts; int /*<<< orphan*/  mac_rx_ctrl_pkt; int /*<<< orphan*/  mac_rx_pause_cnt; int /*<<< orphan*/  mac_rx_bcast_pkts; int /*<<< orphan*/  mac_rx_mcast_pkts; int /*<<< orphan*/  mac_rx_bytes; int /*<<< orphan*/  mac_rx_frames; int /*<<< orphan*/  mac_tx_gt_1518b_pkts; int /*<<< orphan*/  mac_tx_lt_1518b_pkts; int /*<<< orphan*/  mac_tx_lt_1023b_pkts; int /*<<< orphan*/  mac_tx_lt_511b_pkts; int /*<<< orphan*/  mac_tx_lt_255b_pkts; int /*<<< orphan*/  mac_tx_lt_127b_pkts; int /*<<< orphan*/  mac_tx_lt_64b_pkts; int /*<<< orphan*/  mac_tx_ctrl_pkt; int /*<<< orphan*/  mac_tx_pause_cnt; int /*<<< orphan*/  mac_tx_bcast_pkts; int /*<<< orphan*/  mac_tx_mcast_pkts; int /*<<< orphan*/  mac_tx_bytes; int /*<<< orphan*/  mac_tx_frames; } ;
struct __qlcnic_esw_statistics {int /*<<< orphan*/  numbytes; int /*<<< orphan*/  local_frames; int /*<<< orphan*/  errors; int /*<<< orphan*/  dropped_frames; int /*<<< orphan*/  broadcast_frames; int /*<<< orphan*/  multicast_frames; int /*<<< orphan*/  unicast_frames; } ;

/* Variables and functions */
 int QLCNIC_ESW_STATS ; 
 void* QLCNIC_FILL_STATS (int /*<<< orphan*/ ) ; 
 int QLCNIC_MAC_STATS ; 

__attribute__((used)) static u64 *qlcnic_fill_stats(u64 *data, void *stats, int type)
{
	if (type == QLCNIC_MAC_STATS) {
		struct qlcnic_mac_statistics *mac_stats =
					(struct qlcnic_mac_statistics *)stats;
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_frames);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_bytes);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_mcast_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_bcast_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_pause_cnt);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_ctrl_pkt);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_64b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_127b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_255b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_511b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_1023b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_1518b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_gt_1518b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_frames);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_bytes);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_mcast_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_bcast_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_pause_cnt);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_ctrl_pkt);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_64b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_127b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_255b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_511b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_1023b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_1518b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_gt_1518b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_length_error);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_length_small);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_length_large);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_jabber);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_dropped);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_crc_error);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_align_error);
	} else if (type == QLCNIC_ESW_STATS) {
		struct __qlcnic_esw_statistics *esw_stats =
				(struct __qlcnic_esw_statistics *)stats;
		*data++ = QLCNIC_FILL_STATS(esw_stats->unicast_frames);
		*data++ = QLCNIC_FILL_STATS(esw_stats->multicast_frames);
		*data++ = QLCNIC_FILL_STATS(esw_stats->broadcast_frames);
		*data++ = QLCNIC_FILL_STATS(esw_stats->dropped_frames);
		*data++ = QLCNIC_FILL_STATS(esw_stats->errors);
		*data++ = QLCNIC_FILL_STATS(esw_stats->local_frames);
		*data++ = QLCNIC_FILL_STATS(esw_stats->numbytes);
	}
	return data;
}