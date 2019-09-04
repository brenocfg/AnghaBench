#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long uint64_t ;
struct throtl_grp {unsigned long last_check_time; int** bps; unsigned long* last_bytes_disp; unsigned long* last_low_overflow_time; int** iops; unsigned long* last_io_disp; TYPE_3__* td; } ;
struct TYPE_8__ {TYPE_2__* blkcg; } ;
struct TYPE_7__ {scalar_t__ limit_index; scalar_t__ throtl_slice; int /*<<< orphan*/ * limit_valid; } ;
struct TYPE_5__ {int /*<<< orphan*/  children; } ;
struct TYPE_6__ {TYPE_1__ css; } ;

/* Variables and functions */
 unsigned long HZ ; 
 size_t LIMIT_LOW ; 
 scalar_t__ LIMIT_MAX ; 
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ tg_last_low_overflow_time (struct throtl_grp*) ; 
 TYPE_4__* tg_to_blkg (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_downgrade_state (TYPE_3__*,size_t) ; 
 scalar_t__ throtl_hierarchy_can_downgrade (struct throtl_grp*) ; 
 scalar_t__ time_after (scalar_t__,unsigned long) ; 
 scalar_t__ time_before (unsigned long,scalar_t__) ; 

__attribute__((used)) static void throtl_downgrade_check(struct throtl_grp *tg)
{
	uint64_t bps;
	unsigned int iops;
	unsigned long elapsed_time;
	unsigned long now = jiffies;

	if (tg->td->limit_index != LIMIT_MAX ||
	    !tg->td->limit_valid[LIMIT_LOW])
		return;
	if (!list_empty(&tg_to_blkg(tg)->blkcg->css.children))
		return;
	if (time_after(tg->last_check_time + tg->td->throtl_slice, now))
		return;

	elapsed_time = now - tg->last_check_time;
	tg->last_check_time = now;

	if (time_before(now, tg_last_low_overflow_time(tg) +
			tg->td->throtl_slice))
		return;

	if (tg->bps[READ][LIMIT_LOW]) {
		bps = tg->last_bytes_disp[READ] * HZ;
		do_div(bps, elapsed_time);
		if (bps >= tg->bps[READ][LIMIT_LOW])
			tg->last_low_overflow_time[READ] = now;
	}

	if (tg->bps[WRITE][LIMIT_LOW]) {
		bps = tg->last_bytes_disp[WRITE] * HZ;
		do_div(bps, elapsed_time);
		if (bps >= tg->bps[WRITE][LIMIT_LOW])
			tg->last_low_overflow_time[WRITE] = now;
	}

	if (tg->iops[READ][LIMIT_LOW]) {
		iops = tg->last_io_disp[READ] * HZ / elapsed_time;
		if (iops >= tg->iops[READ][LIMIT_LOW])
			tg->last_low_overflow_time[READ] = now;
	}

	if (tg->iops[WRITE][LIMIT_LOW]) {
		iops = tg->last_io_disp[WRITE] * HZ / elapsed_time;
		if (iops >= tg->iops[WRITE][LIMIT_LOW])
			tg->last_low_overflow_time[WRITE] = now;
	}

	/*
	 * If cgroup is below low limit, consider downgrade and throttle other
	 * cgroups
	 */
	if (throtl_hierarchy_can_downgrade(tg))
		throtl_downgrade_state(tg->td, LIMIT_LOW);

	tg->last_bytes_disp[READ] = 0;
	tg->last_bytes_disp[WRITE] = 0;
	tg->last_io_disp[READ] = 0;
	tg->last_io_disp[WRITE] = 0;
}