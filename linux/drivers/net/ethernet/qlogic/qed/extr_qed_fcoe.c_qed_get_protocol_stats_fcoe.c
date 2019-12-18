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
struct qed_mcp_fcoe_stats {int /*<<< orphan*/  login_failure; int /*<<< orphan*/  fcs_err; scalar_t__ tx_pkts; scalar_t__ rx_pkts; } ;
struct qed_fcoe_stats {int /*<<< orphan*/  fcoe_silent_drop_pkt_crc_error_cnt; scalar_t__ fcoe_tx_other_pkt_cnt; scalar_t__ fcoe_tx_xfer_pkt_cnt; scalar_t__ fcoe_tx_data_pkt_cnt; scalar_t__ fcoe_rx_other_pkt_cnt; scalar_t__ fcoe_rx_xfer_pkt_cnt; scalar_t__ fcoe_rx_data_pkt_cnt; } ;
struct qed_fcoe_cb_ops {int /*<<< orphan*/  (* get_login_failures ) (void*) ;} ;
struct TYPE_2__ {struct qed_fcoe_cb_ops* fcoe; } ;
struct qed_dev {void* ops_cookie; TYPE_1__ protocol_ops; } ;
typedef  int /*<<< orphan*/  proto_stats ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QED_MSG_STORAGE ; 
 int /*<<< orphan*/  memset (struct qed_fcoe_stats*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qed_fcoe_stats (struct qed_dev*,struct qed_fcoe_stats*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void qed_get_protocol_stats_fcoe(struct qed_dev *cdev,
				 struct qed_mcp_fcoe_stats *stats)
{
	struct qed_fcoe_stats proto_stats;

	/* Retrieve FW statistics */
	memset(&proto_stats, 0, sizeof(proto_stats));
	if (qed_fcoe_stats(cdev, &proto_stats)) {
		DP_VERBOSE(cdev, QED_MSG_STORAGE,
			   "Failed to collect FCoE statistics\n");
		return;
	}

	/* Translate FW statistics into struct */
	stats->rx_pkts = proto_stats.fcoe_rx_data_pkt_cnt +
			 proto_stats.fcoe_rx_xfer_pkt_cnt +
			 proto_stats.fcoe_rx_other_pkt_cnt;
	stats->tx_pkts = proto_stats.fcoe_tx_data_pkt_cnt +
			 proto_stats.fcoe_tx_xfer_pkt_cnt +
			 proto_stats.fcoe_tx_other_pkt_cnt;
	stats->fcs_err = proto_stats.fcoe_silent_drop_pkt_crc_error_cnt;

	/* Request protocol driver to fill-in the rest */
	if (cdev->protocol_ops.fcoe && cdev->ops_cookie) {
		struct qed_fcoe_cb_ops *ops = cdev->protocol_ops.fcoe;
		void *cookie = cdev->ops_cookie;

		if (ops->get_login_failures)
			stats->login_failure = ops->get_login_failures(cookie);
	}
}