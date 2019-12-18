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
typedef  int u8 ;
struct stats_query_header {int dummy; } ;
struct stats_query_cmd_group {int dummy; } ;
struct stats_counter {int dummy; } ;
struct per_queue_stats {int dummy; } ;
struct per_port_stats {int dummy; } ;
struct per_pf_stats {int dummy; } ;
struct fcoe_statistics_params {int dummy; } ;
struct bnx2x_fw_stats_req {int dummy; } ;
struct bnx2x_fw_stats_data {int dummy; } ;
struct bnx2x {int fw_stats_num; int fw_stats_req_sz; int fw_stats_data_sz; scalar_t__ fw_stats_data_mapping; scalar_t__ fw_stats_req_mapping; scalar_t__ fw_stats_mapping; scalar_t__ fw_stats; struct bnx2x_fw_stats_data* fw_stats_data; struct bnx2x_fw_stats_req* fw_stats_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int BNX2X_NUM_ETH_QUEUES (struct bnx2x*) ; 
 scalar_t__ BNX2X_PCI_ALLOC (scalar_t__*,int) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int ENOMEM ; 
 scalar_t__ IS_SRIOV (struct bnx2x*) ; 
 scalar_t__ NO_FCOE (struct bnx2x*) ; 
 int STATS_QUERY_CMD_COUNT ; 
 int /*<<< orphan*/  U64_HI (scalar_t__) ; 
 int /*<<< orphan*/  U64_LO (scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_free_fw_stats_mem (struct bnx2x*) ; 
 int bnx2x_vf_headroom (struct bnx2x*) ; 

__attribute__((used)) static int bnx2x_alloc_fw_stats_mem(struct bnx2x *bp)
{
	int num_groups, vf_headroom = 0;
	int is_fcoe_stats = NO_FCOE(bp) ? 0 : 1;

	/* number of queues for statistics is number of eth queues + FCoE */
	u8 num_queue_stats = BNX2X_NUM_ETH_QUEUES(bp) + is_fcoe_stats;

	/* Total number of FW statistics requests =
	 * 1 for port stats + 1 for PF stats + potential 2 for FCoE (fcoe proper
	 * and fcoe l2 queue) stats + num of queues (which includes another 1
	 * for fcoe l2 queue if applicable)
	 */
	bp->fw_stats_num = 2 + is_fcoe_stats + num_queue_stats;

	/* vf stats appear in the request list, but their data is allocated by
	 * the VFs themselves. We don't include them in the bp->fw_stats_num as
	 * it is used to determine where to place the vf stats queries in the
	 * request struct
	 */
	if (IS_SRIOV(bp))
		vf_headroom = bnx2x_vf_headroom(bp);

	/* Request is built from stats_query_header and an array of
	 * stats_query_cmd_group each of which contains
	 * STATS_QUERY_CMD_COUNT rules. The real number or requests is
	 * configured in the stats_query_header.
	 */
	num_groups =
		(((bp->fw_stats_num + vf_headroom) / STATS_QUERY_CMD_COUNT) +
		 (((bp->fw_stats_num + vf_headroom) % STATS_QUERY_CMD_COUNT) ?
		 1 : 0));

	DP(BNX2X_MSG_SP, "stats fw_stats_num %d, vf headroom %d, num_groups %d\n",
	   bp->fw_stats_num, vf_headroom, num_groups);
	bp->fw_stats_req_sz = sizeof(struct stats_query_header) +
		num_groups * sizeof(struct stats_query_cmd_group);

	/* Data for statistics requests + stats_counter
	 * stats_counter holds per-STORM counters that are incremented
	 * when STORM has finished with the current request.
	 * memory for FCoE offloaded statistics are counted anyway,
	 * even if they will not be sent.
	 * VF stats are not accounted for here as the data of VF stats is stored
	 * in memory allocated by the VF, not here.
	 */
	bp->fw_stats_data_sz = sizeof(struct per_port_stats) +
		sizeof(struct per_pf_stats) +
		sizeof(struct fcoe_statistics_params) +
		sizeof(struct per_queue_stats) * num_queue_stats +
		sizeof(struct stats_counter);

	bp->fw_stats = BNX2X_PCI_ALLOC(&bp->fw_stats_mapping,
				       bp->fw_stats_data_sz + bp->fw_stats_req_sz);
	if (!bp->fw_stats)
		goto alloc_mem_err;

	/* Set shortcuts */
	bp->fw_stats_req = (struct bnx2x_fw_stats_req *)bp->fw_stats;
	bp->fw_stats_req_mapping = bp->fw_stats_mapping;
	bp->fw_stats_data = (struct bnx2x_fw_stats_data *)
		((u8 *)bp->fw_stats + bp->fw_stats_req_sz);
	bp->fw_stats_data_mapping = bp->fw_stats_mapping +
		bp->fw_stats_req_sz;

	DP(BNX2X_MSG_SP, "statistics request base address set to %x %x\n",
	   U64_HI(bp->fw_stats_req_mapping),
	   U64_LO(bp->fw_stats_req_mapping));
	DP(BNX2X_MSG_SP, "statistics data base address set to %x %x\n",
	   U64_HI(bp->fw_stats_data_mapping),
	   U64_LO(bp->fw_stats_data_mapping));
	return 0;

alloc_mem_err:
	bnx2x_free_fw_stats_mem(bp);
	BNX2X_ERR("Can't allocate FW stats memory\n");
	return -ENOMEM;
}