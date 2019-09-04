#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_list {TYPE_3__* q; } ;
struct TYPE_6__ {TYPE_2__* backing_dev_info; struct request_list root_rl; } ;
struct TYPE_4__ {int /*<<< orphan*/  congested; } ;
struct TYPE_5__ {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_wb_congested (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void blk_clear_congested(struct request_list *rl, int sync)
{
#ifdef CONFIG_CGROUP_WRITEBACK
	clear_wb_congested(rl->blkg->wb_congested, sync);
#else
	/*
	 * If !CGROUP_WRITEBACK, all blkg's map to bdi->wb and we shouldn't
	 * flip its congestion state for events on other blkcgs.
	 */
	if (rl == &rl->q->root_rl)
		clear_wb_congested(rl->q->backing_dev_info->wb.congested, sync);
#endif
}