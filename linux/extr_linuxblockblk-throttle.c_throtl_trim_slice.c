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
typedef  unsigned long u64 ;
struct throtl_grp {unsigned long* slice_start; unsigned long* bytes_disp; unsigned long* io_disp; int /*<<< orphan*/ * slice_end; int /*<<< orphan*/  service_queue; TYPE_1__* td; } ;
struct TYPE_2__ {unsigned long throtl_slice; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned long HZ ; 
 int READ ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 unsigned long jiffies ; 
 unsigned long tg_bps_limit (struct throtl_grp*,int) ; 
 unsigned long tg_iops_limit (struct throtl_grp*,int) ; 
 int /*<<< orphan*/  throtl_log (int /*<<< orphan*/ *,char*,char,unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  throtl_set_slice_end (struct throtl_grp*,int,unsigned long) ; 
 scalar_t__ throtl_slice_used (struct throtl_grp*,int) ; 
 int /*<<< orphan*/  time_before (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline void throtl_trim_slice(struct throtl_grp *tg, bool rw)
{
	unsigned long nr_slices, time_elapsed, io_trim;
	u64 bytes_trim, tmp;

	BUG_ON(time_before(tg->slice_end[rw], tg->slice_start[rw]));

	/*
	 * If bps are unlimited (-1), then time slice don't get
	 * renewed. Don't try to trim the slice if slice is used. A new
	 * slice will start when appropriate.
	 */
	if (throtl_slice_used(tg, rw))
		return;

	/*
	 * A bio has been dispatched. Also adjust slice_end. It might happen
	 * that initially cgroup limit was very low resulting in high
	 * slice_end, but later limit was bumped up and bio was dispached
	 * sooner, then we need to reduce slice_end. A high bogus slice_end
	 * is bad because it does not allow new slice to start.
	 */

	throtl_set_slice_end(tg, rw, jiffies + tg->td->throtl_slice);

	time_elapsed = jiffies - tg->slice_start[rw];

	nr_slices = time_elapsed / tg->td->throtl_slice;

	if (!nr_slices)
		return;
	tmp = tg_bps_limit(tg, rw) * tg->td->throtl_slice * nr_slices;
	do_div(tmp, HZ);
	bytes_trim = tmp;

	io_trim = (tg_iops_limit(tg, rw) * tg->td->throtl_slice * nr_slices) /
		HZ;

	if (!bytes_trim && !io_trim)
		return;

	if (tg->bytes_disp[rw] >= bytes_trim)
		tg->bytes_disp[rw] -= bytes_trim;
	else
		tg->bytes_disp[rw] = 0;

	if (tg->io_disp[rw] >= io_trim)
		tg->io_disp[rw] -= io_trim;
	else
		tg->io_disp[rw] = 0;

	tg->slice_start[rw] += nr_slices * tg->td->throtl_slice;

	throtl_log(&tg->service_queue,
		   "[%c] trim slice nr=%lu bytes=%llu io=%lu start=%lu end=%lu jiffies=%lu",
		   rw == READ ? 'R' : 'W', nr_slices, bytes_trim, io_trim,
		   tg->slice_start[rw], tg->slice_end[rw], jiffies);
}