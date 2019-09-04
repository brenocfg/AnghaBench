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
struct bnxt_coal {int coal_ticks; int coal_bufs; int coal_ticks_irq; int coal_bufs_irq; int idle_thresh; int bufs_per_record; int budget; } ;
struct bnxt {int /*<<< orphan*/  stats_coal_ticks; struct bnxt_coal tx_coal; struct bnxt_coal rx_coal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_DEF_STATS_COAL_TICKS ; 

__attribute__((used)) static void bnxt_init_dflt_coal(struct bnxt *bp)
{
	struct bnxt_coal *coal;

	/* Tick values in micro seconds.
	 * 1 coal_buf x bufs_per_record = 1 completion record.
	 */
	coal = &bp->rx_coal;
	coal->coal_ticks = 14;
	coal->coal_bufs = 30;
	coal->coal_ticks_irq = 1;
	coal->coal_bufs_irq = 2;
	coal->idle_thresh = 50;
	coal->bufs_per_record = 2;
	coal->budget = 64;		/* NAPI budget */

	coal = &bp->tx_coal;
	coal->coal_ticks = 28;
	coal->coal_bufs = 30;
	coal->coal_ticks_irq = 2;
	coal->coal_bufs_irq = 2;
	coal->bufs_per_record = 1;

	bp->stats_coal_ticks = BNXT_DEF_STATS_COAL_TICKS;
}