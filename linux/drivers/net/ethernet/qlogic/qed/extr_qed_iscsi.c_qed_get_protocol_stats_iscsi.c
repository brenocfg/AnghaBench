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
struct qed_mcp_iscsi_stats {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_pdus; int /*<<< orphan*/  rx_pdus; } ;
struct qed_iscsi_stats {int /*<<< orphan*/  iscsi_tx_bytes_cnt; int /*<<< orphan*/  iscsi_rx_bytes_cnt; int /*<<< orphan*/  iscsi_tx_total_pdu_cnt; int /*<<< orphan*/  iscsi_rx_total_pdu_cnt; } ;
struct qed_dev {int dummy; } ;
typedef  int /*<<< orphan*/  proto_stats ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QED_MSG_STORAGE ; 
 int /*<<< orphan*/  memset (struct qed_iscsi_stats*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qed_iscsi_stats (struct qed_dev*,struct qed_iscsi_stats*) ; 

void qed_get_protocol_stats_iscsi(struct qed_dev *cdev,
				  struct qed_mcp_iscsi_stats *stats)
{
	struct qed_iscsi_stats proto_stats;

	/* Retrieve FW statistics */
	memset(&proto_stats, 0, sizeof(proto_stats));
	if (qed_iscsi_stats(cdev, &proto_stats)) {
		DP_VERBOSE(cdev, QED_MSG_STORAGE,
			   "Failed to collect ISCSI statistics\n");
		return;
	}

	/* Translate FW statistics into struct */
	stats->rx_pdus = proto_stats.iscsi_rx_total_pdu_cnt;
	stats->tx_pdus = proto_stats.iscsi_tx_total_pdu_cnt;
	stats->rx_bytes = proto_stats.iscsi_rx_bytes_cnt;
	stats->tx_bytes = proto_stats.iscsi_tx_bytes_cnt;
}