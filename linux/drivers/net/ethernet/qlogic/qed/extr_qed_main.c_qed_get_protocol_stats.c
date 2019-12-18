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
struct TYPE_3__ {int fcs_err; int /*<<< orphan*/  ucast_tx_pkts; int /*<<< orphan*/  ucast_rx_pkts; } ;
union qed_mcp_protocol_stats {int /*<<< orphan*/  iscsi_stats; int /*<<< orphan*/  fcoe_stats; TYPE_1__ lan_stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_ucast_pkts; int /*<<< orphan*/  rx_ucast_pkts; } ;
struct qed_eth_stats {TYPE_2__ common; } ;
struct qed_dev {int dummy; } ;
typedef  enum qed_mcp_protocol_type { ____Placeholder_qed_mcp_protocol_type } qed_mcp_protocol_type ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,int) ; 
#define  QED_MCP_FCOE_STATS 130 
#define  QED_MCP_ISCSI_STATS 129 
#define  QED_MCP_LAN_STATS 128 
 int /*<<< orphan*/  QED_MSG_SP ; 
 int /*<<< orphan*/  memset (union qed_mcp_protocol_stats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_get_protocol_stats_fcoe (struct qed_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_get_protocol_stats_iscsi (struct qed_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_get_vport_stats (struct qed_dev*,struct qed_eth_stats*) ; 

void qed_get_protocol_stats(struct qed_dev *cdev,
			    enum qed_mcp_protocol_type type,
			    union qed_mcp_protocol_stats *stats)
{
	struct qed_eth_stats eth_stats;

	memset(stats, 0, sizeof(*stats));

	switch (type) {
	case QED_MCP_LAN_STATS:
		qed_get_vport_stats(cdev, &eth_stats);
		stats->lan_stats.ucast_rx_pkts =
					eth_stats.common.rx_ucast_pkts;
		stats->lan_stats.ucast_tx_pkts =
					eth_stats.common.tx_ucast_pkts;
		stats->lan_stats.fcs_err = -1;
		break;
	case QED_MCP_FCOE_STATS:
		qed_get_protocol_stats_fcoe(cdev, &stats->fcoe_stats);
		break;
	case QED_MCP_ISCSI_STATS:
		qed_get_protocol_stats_iscsi(cdev, &stats->iscsi_stats);
		break;
	default:
		DP_VERBOSE(cdev, QED_MSG_SP,
			   "Invalid protocol type = %d\n", type);
		return;
	}
}