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
struct net_device_stats {scalar_t__ rx_over_errors; scalar_t__ rx_length_errors; scalar_t__ rx_crc_errors; int /*<<< orphan*/  multicast; scalar_t__ rx_errors; int /*<<< orphan*/  rx_dropped; scalar_t__ tx_dropped; } ;
struct TYPE_4__ {scalar_t__ mac_rx_oversize_pkt_num; scalar_t__ mac_rx_undersize_pkt_num; scalar_t__ mac_rx_fcs_err_pkt_num; scalar_t__ mac_rx_multi_pkt_num; int /*<<< orphan*/  mac_tx_multi_pkt_num; } ;
struct TYPE_3__ {scalar_t__ igu_rx_no_sof_pkt; scalar_t__ igu_rx_no_eof_pkt; scalar_t__ ssu_key_drop_num; scalar_t__ ppp_key_drop_num; int /*<<< orphan*/  ssu_full_drop_num; } ;
struct hclge_hw_stats {TYPE_2__ mac_stats; TYPE_1__ all_32_bit_stats; } ;

/* Variables and functions */

__attribute__((used)) static void hclge_update_netstat(struct hclge_hw_stats *hw_stats,
				 struct net_device_stats *net_stats)
{
	net_stats->tx_dropped = 0;
	net_stats->rx_dropped = hw_stats->all_32_bit_stats.ssu_full_drop_num;
	net_stats->rx_dropped += hw_stats->all_32_bit_stats.ppp_key_drop_num;
	net_stats->rx_dropped += hw_stats->all_32_bit_stats.ssu_key_drop_num;

	net_stats->rx_errors = hw_stats->mac_stats.mac_rx_oversize_pkt_num;
	net_stats->rx_errors += hw_stats->mac_stats.mac_rx_undersize_pkt_num;
	net_stats->rx_errors += hw_stats->all_32_bit_stats.igu_rx_no_eof_pkt;
	net_stats->rx_errors += hw_stats->all_32_bit_stats.igu_rx_no_sof_pkt;
	net_stats->rx_errors += hw_stats->mac_stats.mac_rx_fcs_err_pkt_num;

	net_stats->multicast = hw_stats->mac_stats.mac_tx_multi_pkt_num;
	net_stats->multicast += hw_stats->mac_stats.mac_rx_multi_pkt_num;

	net_stats->rx_crc_errors = hw_stats->mac_stats.mac_rx_fcs_err_pkt_num;
	net_stats->rx_length_errors =
		hw_stats->mac_stats.mac_rx_undersize_pkt_num;
	net_stats->rx_length_errors +=
		hw_stats->mac_stats.mac_rx_oversize_pkt_num;
	net_stats->rx_over_errors =
		hw_stats->mac_stats.mac_rx_oversize_pkt_num;
}