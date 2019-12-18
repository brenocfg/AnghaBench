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
struct timer_list {int dummy; } ;
struct bnx2 {int flags; int hc_cmd; int phy_flags; scalar_t__ current_interval; int /*<<< orphan*/  timer; scalar_t__ stats_ticks; TYPE_1__* stats_blk; int /*<<< orphan*/  intr_sem; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_FwRxDrop; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5706 ; 
 int BNX2_FLAG_BROKEN_STATS ; 
 int BNX2_FLAG_ONE_SHOT_MSI ; 
 int BNX2_FLAG_USING_MSI ; 
 int /*<<< orphan*/  BNX2_FW_RX_DROP_COUNT ; 
 int /*<<< orphan*/  BNX2_HC_COMMAND ; 
 int BNX2_HC_COMMAND_STATS_NOW ; 
 int BNX2_PHY_FLAG_SERDES ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2_5706_serdes_timer (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_5708_serdes_timer (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_chk_missed_msi (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_reg_rd_ind (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_send_heart_beat (struct bnx2*) ; 
 struct bnx2* bp ; 
 struct bnx2* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void
bnx2_timer(struct timer_list *t)
{
	struct bnx2 *bp = from_timer(bp, t, timer);

	if (!netif_running(bp->dev))
		return;

	if (atomic_read(&bp->intr_sem) != 0)
		goto bnx2_restart_timer;

	if ((bp->flags & (BNX2_FLAG_USING_MSI | BNX2_FLAG_ONE_SHOT_MSI)) ==
	     BNX2_FLAG_USING_MSI)
		bnx2_chk_missed_msi(bp);

	bnx2_send_heart_beat(bp);

	bp->stats_blk->stat_FwRxDrop =
		bnx2_reg_rd_ind(bp, BNX2_FW_RX_DROP_COUNT);

	/* workaround occasional corrupted counters */
	if ((bp->flags & BNX2_FLAG_BROKEN_STATS) && bp->stats_ticks)
		BNX2_WR(bp, BNX2_HC_COMMAND, bp->hc_cmd |
			BNX2_HC_COMMAND_STATS_NOW);

	if (bp->phy_flags & BNX2_PHY_FLAG_SERDES) {
		if (BNX2_CHIP(bp) == BNX2_CHIP_5706)
			bnx2_5706_serdes_timer(bp);
		else
			bnx2_5708_serdes_timer(bp);
	}

bnx2_restart_timer:
	mod_timer(&bp->timer, jiffies + bp->current_interval);
}