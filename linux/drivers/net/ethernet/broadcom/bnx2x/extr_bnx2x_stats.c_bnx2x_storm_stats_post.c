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
struct bnx2x {int stats_pending; int /*<<< orphan*/  fw_stats_req_mapping; TYPE_1__* fw_stats_req; int /*<<< orphan*/  stats_counter; } ;
struct TYPE_4__ {int /*<<< orphan*/  drv_stats_counter; } ;
struct TYPE_3__ {TYPE_2__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_STATS ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NONE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_COMMON_STAT_QUERY ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_dp_stats (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_iov_adjust_stats_req (struct bnx2x*) ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_storm_stats_post(struct bnx2x *bp)
{
	int rc;

	if (bp->stats_pending)
		return;

	bp->fw_stats_req->hdr.drv_stats_counter =
		cpu_to_le16(bp->stats_counter++);

	DP(BNX2X_MSG_STATS, "Sending statistics ramrod %d\n",
	   le16_to_cpu(bp->fw_stats_req->hdr.drv_stats_counter));

	/* adjust the ramrod to include VF queues statistics */
	bnx2x_iov_adjust_stats_req(bp);
	bnx2x_dp_stats(bp);

	/* send FW stats ramrod */
	rc = bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_STAT_QUERY, 0,
			   U64_HI(bp->fw_stats_req_mapping),
			   U64_LO(bp->fw_stats_req_mapping),
			   NONE_CONNECTION_TYPE);
	if (rc == 0)
		bp->stats_pending = 1;
}