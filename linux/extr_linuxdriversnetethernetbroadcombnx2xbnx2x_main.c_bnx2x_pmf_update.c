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
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ int_block; } ;
struct TYPE_4__ {int pmf; } ;
struct bnx2x {TYPE_1__ common; int /*<<< orphan*/  period_task; TYPE_2__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_MCP ; 
 int BP_PORT (struct bnx2x*) ; 
 int BP_VN (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ HC_REG_LEADING_EDGE_0 ; 
 scalar_t__ HC_REG_TRAILING_EDGE_0 ; 
 scalar_t__ IGU_REG_LEADING_EDGE_LATCH ; 
 scalar_t__ IGU_REG_TRAILING_EDGE_LATCH ; 
 scalar_t__ INT_BLOCK_HC ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  STATS_EVENT_PMF ; 
 int /*<<< orphan*/  bnx2x_dcbx_pmf_update (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_stats_handle (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void bnx2x_pmf_update(struct bnx2x *bp)
{
	int port = BP_PORT(bp);
	u32 val;

	bp->port.pmf = 1;
	DP(BNX2X_MSG_MCP, "pmf %d\n", bp->port.pmf);

	/*
	 * We need the mb() to ensure the ordering between the writing to
	 * bp->port.pmf here and reading it from the bnx2x_periodic_task().
	 */
	smp_mb();

	/* queue a periodic task */
	queue_delayed_work(bnx2x_wq, &bp->period_task, 0);

	bnx2x_dcbx_pmf_update(bp);

	/* enable nig attention */
	val = (0xff0f | (1 << (BP_VN(bp) + 4)));
	if (bp->common.int_block == INT_BLOCK_HC) {
		REG_WR(bp, HC_REG_TRAILING_EDGE_0 + port*8, val);
		REG_WR(bp, HC_REG_LEADING_EDGE_0 + port*8, val);
	} else if (!CHIP_IS_E1x(bp)) {
		REG_WR(bp, IGU_REG_TRAILING_EDGE_LATCH, val);
		REG_WR(bp, IGU_REG_LEADING_EDGE_LATCH, val);
	}

	bnx2x_stats_handle(bp, STATS_EVENT_PMF);
}