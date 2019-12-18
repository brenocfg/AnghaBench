#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct qede_stats_common {int /*<<< orphan*/  ptp_skip_txts; int /*<<< orphan*/  link_change_count; int /*<<< orphan*/  tx_mac_ctrl_frames; int /*<<< orphan*/  brb_discards; int /*<<< orphan*/  brb_truncates; int /*<<< orphan*/  tx_pfc_frames; int /*<<< orphan*/  tx_pause_frames; int /*<<< orphan*/  tx_1024_to_1518_byte_packets; int /*<<< orphan*/  tx_512_to_1023_byte_packets; int /*<<< orphan*/  tx_256_to_511_byte_packets; int /*<<< orphan*/  tx_128_to_255_byte_packets; int /*<<< orphan*/  tx_65_to_127_byte_packets; int /*<<< orphan*/  tx_64_byte_packets; int /*<<< orphan*/  rx_fragments; int /*<<< orphan*/  rx_undersize_packets; int /*<<< orphan*/  rx_jabbers; int /*<<< orphan*/  rx_oversize_packets; int /*<<< orphan*/  rx_carrier_errors; int /*<<< orphan*/  rx_align_errors; int /*<<< orphan*/  rx_pfc_frames; int /*<<< orphan*/  rx_pause_frames; int /*<<< orphan*/  rx_mac_crtl_frames; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_1024_to_1518_byte_packets; int /*<<< orphan*/  rx_512_to_1023_byte_packets; int /*<<< orphan*/  rx_256_to_511_byte_packets; int /*<<< orphan*/  rx_128_to_255_byte_packets; int /*<<< orphan*/  rx_65_to_127_byte_packets; int /*<<< orphan*/  rx_64_byte_packets; int /*<<< orphan*/  coalesced_bytes; int /*<<< orphan*/  non_coalesced_pkts; int /*<<< orphan*/  coalesced_aborts_num; int /*<<< orphan*/  coalesced_events; int /*<<< orphan*/  coalesced_pkts; int /*<<< orphan*/  tx_err_drop_pkts; int /*<<< orphan*/  tx_bcast_pkts; int /*<<< orphan*/  tx_mcast_pkts; int /*<<< orphan*/  tx_ucast_pkts; int /*<<< orphan*/  tx_bcast_bytes; int /*<<< orphan*/  tx_mcast_bytes; int /*<<< orphan*/  tx_ucast_bytes; int /*<<< orphan*/  gft_filter_drop; int /*<<< orphan*/  mac_filter_discards; int /*<<< orphan*/  mftag_filter_discards; int /*<<< orphan*/  rx_bcast_pkts; int /*<<< orphan*/  rx_mcast_pkts; int /*<<< orphan*/  rx_ucast_pkts; int /*<<< orphan*/  rx_bcast_bytes; int /*<<< orphan*/  rx_mcast_bytes; int /*<<< orphan*/  rx_ucast_bytes; int /*<<< orphan*/  ttl0_discard; int /*<<< orphan*/  packet_too_big_discard; int /*<<< orphan*/  no_buff_discards; } ;
struct qede_stats_bb {int /*<<< orphan*/  tx_total_collisions; int /*<<< orphan*/  tx_lpi_entry_count; int /*<<< orphan*/  tx_9217_to_16383_byte_packets; int /*<<< orphan*/  tx_4096_to_9216_byte_packets; int /*<<< orphan*/  tx_2048_to_4095_byte_packets; int /*<<< orphan*/  tx_1519_to_2047_byte_packets; int /*<<< orphan*/  rx_9217_to_16383_byte_packets; int /*<<< orphan*/  rx_4096_to_9216_byte_packets; int /*<<< orphan*/  rx_2048_to_4095_byte_packets; int /*<<< orphan*/  rx_1519_to_2047_byte_packets; int /*<<< orphan*/  rx_1519_to_1522_byte_packets; } ;
struct qede_stats_ah {int /*<<< orphan*/  tx_1519_to_max_byte_packets; int /*<<< orphan*/  rx_1519_to_max_byte_packets; } ;
struct TYPE_8__ {struct qede_stats_ah ah; struct qede_stats_bb bb; struct qede_stats_common common; } ;
struct qede_dev {TYPE_3__ stats; int /*<<< orphan*/  ptp_skip_txts; int /*<<< orphan*/  cdev; TYPE_4__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_1519_to_max_byte_packets; int /*<<< orphan*/  rx_1519_to_max_byte_packets; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_total_collisions; int /*<<< orphan*/  tx_lpi_entry_count; int /*<<< orphan*/  tx_9217_to_16383_byte_packets; int /*<<< orphan*/  tx_4096_to_9216_byte_packets; int /*<<< orphan*/  tx_2048_to_4095_byte_packets; int /*<<< orphan*/  tx_1519_to_2047_byte_packets; int /*<<< orphan*/  rx_9217_to_16383_byte_packets; int /*<<< orphan*/  rx_4096_to_9216_byte_packets; int /*<<< orphan*/  rx_2048_to_4095_byte_packets; int /*<<< orphan*/  rx_1519_to_2047_byte_packets; int /*<<< orphan*/  rx_1519_to_1522_byte_packets; } ;
struct TYPE_10__ {int /*<<< orphan*/  link_change_count; int /*<<< orphan*/  tx_mac_ctrl_frames; int /*<<< orphan*/  brb_discards; int /*<<< orphan*/  brb_truncates; int /*<<< orphan*/  tx_pfc_frames; int /*<<< orphan*/  tx_pause_frames; int /*<<< orphan*/  tx_1024_to_1518_byte_packets; int /*<<< orphan*/  tx_512_to_1023_byte_packets; int /*<<< orphan*/  tx_256_to_511_byte_packets; int /*<<< orphan*/  tx_128_to_255_byte_packets; int /*<<< orphan*/  tx_65_to_127_byte_packets; int /*<<< orphan*/  tx_64_byte_packets; int /*<<< orphan*/  rx_fragments; int /*<<< orphan*/  rx_undersize_packets; int /*<<< orphan*/  rx_jabbers; int /*<<< orphan*/  rx_oversize_packets; int /*<<< orphan*/  rx_carrier_errors; int /*<<< orphan*/  rx_align_errors; int /*<<< orphan*/  rx_pfc_frames; int /*<<< orphan*/  rx_pause_frames; int /*<<< orphan*/  rx_mac_crtl_frames; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_1024_to_1518_byte_packets; int /*<<< orphan*/  rx_512_to_1023_byte_packets; int /*<<< orphan*/  rx_256_to_511_byte_packets; int /*<<< orphan*/  rx_128_to_255_byte_packets; int /*<<< orphan*/  rx_65_to_127_byte_packets; int /*<<< orphan*/  rx_64_byte_packets; int /*<<< orphan*/  tpa_coalesced_bytes; int /*<<< orphan*/  tpa_not_coalesced_pkts; int /*<<< orphan*/  tpa_aborts_num; int /*<<< orphan*/  tpa_coalesced_events; int /*<<< orphan*/  tpa_coalesced_pkts; int /*<<< orphan*/  tx_err_drop_pkts; int /*<<< orphan*/  tx_bcast_pkts; int /*<<< orphan*/  tx_mcast_pkts; int /*<<< orphan*/  tx_ucast_pkts; int /*<<< orphan*/  tx_bcast_bytes; int /*<<< orphan*/  tx_mcast_bytes; int /*<<< orphan*/  tx_ucast_bytes; int /*<<< orphan*/  gft_filter_drop; int /*<<< orphan*/  mac_filter_discards; int /*<<< orphan*/  mftag_filter_discards; int /*<<< orphan*/  rx_bcast_pkts; int /*<<< orphan*/  rx_mcast_pkts; int /*<<< orphan*/  rx_ucast_pkts; int /*<<< orphan*/  rx_bcast_bytes; int /*<<< orphan*/  rx_mcast_bytes; int /*<<< orphan*/  rx_ucast_bytes; int /*<<< orphan*/  ttl0_discard; int /*<<< orphan*/  packet_too_big_discard; int /*<<< orphan*/  no_buff_discards; } ;
struct qed_eth_stats {TYPE_2__ ah; TYPE_1__ bb; TYPE_5__ common; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* get_vport_stats ) (int /*<<< orphan*/ ,struct qed_eth_stats*) ;} ;

/* Variables and functions */
 scalar_t__ QEDE_IS_BB (struct qede_dev*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_eth_stats*) ; 

void qede_fill_by_demand_stats(struct qede_dev *edev)
{
	struct qede_stats_common *p_common = &edev->stats.common;
	struct qed_eth_stats stats;

	edev->ops->get_vport_stats(edev->cdev, &stats);

	p_common->no_buff_discards = stats.common.no_buff_discards;
	p_common->packet_too_big_discard = stats.common.packet_too_big_discard;
	p_common->ttl0_discard = stats.common.ttl0_discard;
	p_common->rx_ucast_bytes = stats.common.rx_ucast_bytes;
	p_common->rx_mcast_bytes = stats.common.rx_mcast_bytes;
	p_common->rx_bcast_bytes = stats.common.rx_bcast_bytes;
	p_common->rx_ucast_pkts = stats.common.rx_ucast_pkts;
	p_common->rx_mcast_pkts = stats.common.rx_mcast_pkts;
	p_common->rx_bcast_pkts = stats.common.rx_bcast_pkts;
	p_common->mftag_filter_discards = stats.common.mftag_filter_discards;
	p_common->mac_filter_discards = stats.common.mac_filter_discards;
	p_common->gft_filter_drop = stats.common.gft_filter_drop;

	p_common->tx_ucast_bytes = stats.common.tx_ucast_bytes;
	p_common->tx_mcast_bytes = stats.common.tx_mcast_bytes;
	p_common->tx_bcast_bytes = stats.common.tx_bcast_bytes;
	p_common->tx_ucast_pkts = stats.common.tx_ucast_pkts;
	p_common->tx_mcast_pkts = stats.common.tx_mcast_pkts;
	p_common->tx_bcast_pkts = stats.common.tx_bcast_pkts;
	p_common->tx_err_drop_pkts = stats.common.tx_err_drop_pkts;
	p_common->coalesced_pkts = stats.common.tpa_coalesced_pkts;
	p_common->coalesced_events = stats.common.tpa_coalesced_events;
	p_common->coalesced_aborts_num = stats.common.tpa_aborts_num;
	p_common->non_coalesced_pkts = stats.common.tpa_not_coalesced_pkts;
	p_common->coalesced_bytes = stats.common.tpa_coalesced_bytes;

	p_common->rx_64_byte_packets = stats.common.rx_64_byte_packets;
	p_common->rx_65_to_127_byte_packets =
	    stats.common.rx_65_to_127_byte_packets;
	p_common->rx_128_to_255_byte_packets =
	    stats.common.rx_128_to_255_byte_packets;
	p_common->rx_256_to_511_byte_packets =
	    stats.common.rx_256_to_511_byte_packets;
	p_common->rx_512_to_1023_byte_packets =
	    stats.common.rx_512_to_1023_byte_packets;
	p_common->rx_1024_to_1518_byte_packets =
	    stats.common.rx_1024_to_1518_byte_packets;
	p_common->rx_crc_errors = stats.common.rx_crc_errors;
	p_common->rx_mac_crtl_frames = stats.common.rx_mac_crtl_frames;
	p_common->rx_pause_frames = stats.common.rx_pause_frames;
	p_common->rx_pfc_frames = stats.common.rx_pfc_frames;
	p_common->rx_align_errors = stats.common.rx_align_errors;
	p_common->rx_carrier_errors = stats.common.rx_carrier_errors;
	p_common->rx_oversize_packets = stats.common.rx_oversize_packets;
	p_common->rx_jabbers = stats.common.rx_jabbers;
	p_common->rx_undersize_packets = stats.common.rx_undersize_packets;
	p_common->rx_fragments = stats.common.rx_fragments;
	p_common->tx_64_byte_packets = stats.common.tx_64_byte_packets;
	p_common->tx_65_to_127_byte_packets =
	    stats.common.tx_65_to_127_byte_packets;
	p_common->tx_128_to_255_byte_packets =
	    stats.common.tx_128_to_255_byte_packets;
	p_common->tx_256_to_511_byte_packets =
	    stats.common.tx_256_to_511_byte_packets;
	p_common->tx_512_to_1023_byte_packets =
	    stats.common.tx_512_to_1023_byte_packets;
	p_common->tx_1024_to_1518_byte_packets =
	    stats.common.tx_1024_to_1518_byte_packets;
	p_common->tx_pause_frames = stats.common.tx_pause_frames;
	p_common->tx_pfc_frames = stats.common.tx_pfc_frames;
	p_common->brb_truncates = stats.common.brb_truncates;
	p_common->brb_discards = stats.common.brb_discards;
	p_common->tx_mac_ctrl_frames = stats.common.tx_mac_ctrl_frames;
	p_common->link_change_count = stats.common.link_change_count;
	p_common->ptp_skip_txts = edev->ptp_skip_txts;

	if (QEDE_IS_BB(edev)) {
		struct qede_stats_bb *p_bb = &edev->stats.bb;

		p_bb->rx_1519_to_1522_byte_packets =
		    stats.bb.rx_1519_to_1522_byte_packets;
		p_bb->rx_1519_to_2047_byte_packets =
		    stats.bb.rx_1519_to_2047_byte_packets;
		p_bb->rx_2048_to_4095_byte_packets =
		    stats.bb.rx_2048_to_4095_byte_packets;
		p_bb->rx_4096_to_9216_byte_packets =
		    stats.bb.rx_4096_to_9216_byte_packets;
		p_bb->rx_9217_to_16383_byte_packets =
		    stats.bb.rx_9217_to_16383_byte_packets;
		p_bb->tx_1519_to_2047_byte_packets =
		    stats.bb.tx_1519_to_2047_byte_packets;
		p_bb->tx_2048_to_4095_byte_packets =
		    stats.bb.tx_2048_to_4095_byte_packets;
		p_bb->tx_4096_to_9216_byte_packets =
		    stats.bb.tx_4096_to_9216_byte_packets;
		p_bb->tx_9217_to_16383_byte_packets =
		    stats.bb.tx_9217_to_16383_byte_packets;
		p_bb->tx_lpi_entry_count = stats.bb.tx_lpi_entry_count;
		p_bb->tx_total_collisions = stats.bb.tx_total_collisions;
	} else {
		struct qede_stats_ah *p_ah = &edev->stats.ah;

		p_ah->rx_1519_to_max_byte_packets =
		    stats.ah.rx_1519_to_max_byte_packets;
		p_ah->tx_1519_to_max_byte_packets =
		    stats.ah.tx_1519_to_max_byte_packets;
	}
}