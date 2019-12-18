#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_15__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_14__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct xstorm_per_queue_stats {int /*<<< orphan*/  mcast_pkts_sent; int /*<<< orphan*/  bcast_pkts_sent; int /*<<< orphan*/  ucast_pkts_sent; TYPE_12__ mcast_bytes_sent; TYPE_11__ bcast_bytes_sent; TYPE_10__ ucast_bytes_sent; } ;
struct TYPE_25__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_24__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_23__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct tstorm_per_queue_stats {int /*<<< orphan*/  rcv_mcast_pkts; int /*<<< orphan*/  rcv_bcast_pkts; int /*<<< orphan*/  rcv_ucast_pkts; TYPE_8__ rcv_mcast_bytes; TYPE_7__ rcv_bcast_bytes; TYPE_6__ rcv_ucast_bytes; } ;
struct fcoe_stats_info {int /*<<< orphan*/  tx_frames_lo; int /*<<< orphan*/  tx_frames_hi; int /*<<< orphan*/  tx_bytes_lo; int /*<<< orphan*/  tx_bytes_hi; int /*<<< orphan*/  rx_frames_lo; int /*<<< orphan*/  rx_frames_hi; int /*<<< orphan*/  rx_bytes_lo; int /*<<< orphan*/  rx_bytes_hi; int /*<<< orphan*/  qos_priority; scalar_t__ mac_local; } ;
struct TYPE_17__ {int /*<<< orphan*/  fcoe_tx_pkt_cnt; int /*<<< orphan*/  fcoe_tx_byte_cnt; } ;
struct TYPE_26__ {int /*<<< orphan*/  fcoe_rx_pkt_cnt; int /*<<< orphan*/  fcoe_rx_byte_cnt; } ;
struct fcoe_statistics_params {TYPE_13__ tx_stat; TYPE_9__ rx_stat0; } ;
struct bnx2x_dcbx_app_params {int /*<<< orphan*/ * traffic_type_priority; } ;
struct TYPE_18__ {struct bnx2x_dcbx_app_params app; } ;
struct bnx2x {TYPE_5__* fw_stats_data; int /*<<< orphan*/  fip_mac; TYPE_3__* slowpath; TYPE_1__ dcbx_port_params; } ;
struct TYPE_22__ {struct fcoe_statistics_params fcoe; TYPE_4__* queue_stats; } ;
struct TYPE_21__ {struct xstorm_per_queue_stats xstorm_queue_statistics; struct tstorm_per_queue_stats tstorm_queue_statistics; } ;
struct TYPE_19__ {struct fcoe_stats_info fcoe_stat; } ;
struct TYPE_20__ {TYPE_2__ drv_info_to_mcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_64_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CNIC_CTL_FCOE_STATS_GET_CMD ; 
 int /*<<< orphan*/  CNIC_LOADED (struct bnx2x*) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 size_t FCOE_IDX (struct bnx2x*) ; 
 int /*<<< orphan*/  LE32_0 ; 
 size_t LLFC_TRAFFIC_TYPE_FCOE ; 
 scalar_t__ MAC_PAD ; 
 int /*<<< orphan*/  NO_FCOE (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_cnic_notify (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_drv_info_fcoe_stat(struct bnx2x *bp)
{
	struct bnx2x_dcbx_app_params *app = &bp->dcbx_port_params.app;
	struct fcoe_stats_info *fcoe_stat =
		&bp->slowpath->drv_info_to_mcp.fcoe_stat;

	if (!CNIC_LOADED(bp))
		return;

	memcpy(fcoe_stat->mac_local + MAC_PAD, bp->fip_mac, ETH_ALEN);

	fcoe_stat->qos_priority =
		app->traffic_type_priority[LLFC_TRAFFIC_TYPE_FCOE];

	/* insert FCoE stats from ramrod response */
	if (!NO_FCOE(bp)) {
		struct tstorm_per_queue_stats *fcoe_q_tstorm_stats =
			&bp->fw_stats_data->queue_stats[FCOE_IDX(bp)].
			tstorm_queue_statistics;

		struct xstorm_per_queue_stats *fcoe_q_xstorm_stats =
			&bp->fw_stats_data->queue_stats[FCOE_IDX(bp)].
			xstorm_queue_statistics;

		struct fcoe_statistics_params *fw_fcoe_stat =
			&bp->fw_stats_data->fcoe;

		ADD_64_LE(fcoe_stat->rx_bytes_hi, LE32_0,
			  fcoe_stat->rx_bytes_lo,
			  fw_fcoe_stat->rx_stat0.fcoe_rx_byte_cnt);

		ADD_64_LE(fcoe_stat->rx_bytes_hi,
			  fcoe_q_tstorm_stats->rcv_ucast_bytes.hi,
			  fcoe_stat->rx_bytes_lo,
			  fcoe_q_tstorm_stats->rcv_ucast_bytes.lo);

		ADD_64_LE(fcoe_stat->rx_bytes_hi,
			  fcoe_q_tstorm_stats->rcv_bcast_bytes.hi,
			  fcoe_stat->rx_bytes_lo,
			  fcoe_q_tstorm_stats->rcv_bcast_bytes.lo);

		ADD_64_LE(fcoe_stat->rx_bytes_hi,
			  fcoe_q_tstorm_stats->rcv_mcast_bytes.hi,
			  fcoe_stat->rx_bytes_lo,
			  fcoe_q_tstorm_stats->rcv_mcast_bytes.lo);

		ADD_64_LE(fcoe_stat->rx_frames_hi, LE32_0,
			  fcoe_stat->rx_frames_lo,
			  fw_fcoe_stat->rx_stat0.fcoe_rx_pkt_cnt);

		ADD_64_LE(fcoe_stat->rx_frames_hi, LE32_0,
			  fcoe_stat->rx_frames_lo,
			  fcoe_q_tstorm_stats->rcv_ucast_pkts);

		ADD_64_LE(fcoe_stat->rx_frames_hi, LE32_0,
			  fcoe_stat->rx_frames_lo,
			  fcoe_q_tstorm_stats->rcv_bcast_pkts);

		ADD_64_LE(fcoe_stat->rx_frames_hi, LE32_0,
			  fcoe_stat->rx_frames_lo,
			  fcoe_q_tstorm_stats->rcv_mcast_pkts);

		ADD_64_LE(fcoe_stat->tx_bytes_hi, LE32_0,
			  fcoe_stat->tx_bytes_lo,
			  fw_fcoe_stat->tx_stat.fcoe_tx_byte_cnt);

		ADD_64_LE(fcoe_stat->tx_bytes_hi,
			  fcoe_q_xstorm_stats->ucast_bytes_sent.hi,
			  fcoe_stat->tx_bytes_lo,
			  fcoe_q_xstorm_stats->ucast_bytes_sent.lo);

		ADD_64_LE(fcoe_stat->tx_bytes_hi,
			  fcoe_q_xstorm_stats->bcast_bytes_sent.hi,
			  fcoe_stat->tx_bytes_lo,
			  fcoe_q_xstorm_stats->bcast_bytes_sent.lo);

		ADD_64_LE(fcoe_stat->tx_bytes_hi,
			  fcoe_q_xstorm_stats->mcast_bytes_sent.hi,
			  fcoe_stat->tx_bytes_lo,
			  fcoe_q_xstorm_stats->mcast_bytes_sent.lo);

		ADD_64_LE(fcoe_stat->tx_frames_hi, LE32_0,
			  fcoe_stat->tx_frames_lo,
			  fw_fcoe_stat->tx_stat.fcoe_tx_pkt_cnt);

		ADD_64_LE(fcoe_stat->tx_frames_hi, LE32_0,
			  fcoe_stat->tx_frames_lo,
			  fcoe_q_xstorm_stats->ucast_pkts_sent);

		ADD_64_LE(fcoe_stat->tx_frames_hi, LE32_0,
			  fcoe_stat->tx_frames_lo,
			  fcoe_q_xstorm_stats->bcast_pkts_sent);

		ADD_64_LE(fcoe_stat->tx_frames_hi, LE32_0,
			  fcoe_stat->tx_frames_lo,
			  fcoe_q_xstorm_stats->mcast_pkts_sent);
	}

	/* ask L5 driver to add data to the struct */
	bnx2x_cnic_notify(bp, CNIC_CTL_FCOE_STATS_GET_CMD);
}