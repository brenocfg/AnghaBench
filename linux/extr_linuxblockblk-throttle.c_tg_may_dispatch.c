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
struct TYPE_3__ {scalar_t__* nr_queued; int /*<<< orphan*/ * queued; } ;
struct throtl_grp {int /*<<< orphan*/ * slice_end; TYPE_2__* td; TYPE_1__ service_queue; } ;
struct bio {int dummy; } ;
struct TYPE_4__ {scalar_t__ throtl_slice; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ U64_MAX ; 
 scalar_t__ UINT_MAX ; 
 int bio_data_dir (struct bio*) ; 
 scalar_t__ jiffies ; 
 unsigned long max (unsigned long,unsigned long) ; 
 scalar_t__ tg_bps_limit (struct throtl_grp*,int) ; 
 scalar_t__ tg_iops_limit (struct throtl_grp*,int) ; 
 scalar_t__ tg_with_in_bps_limit (struct throtl_grp*,struct bio*,unsigned long*) ; 
 scalar_t__ tg_with_in_iops_limit (struct throtl_grp*,struct bio*,unsigned long*) ; 
 int /*<<< orphan*/  throtl_extend_slice (struct throtl_grp*,int,scalar_t__) ; 
 struct bio* throtl_peek_queued (int /*<<< orphan*/ *) ; 
 scalar_t__ throtl_slice_used (struct throtl_grp*,int) ; 
 int /*<<< orphan*/  throtl_start_new_slice (struct throtl_grp*,int) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool tg_may_dispatch(struct throtl_grp *tg, struct bio *bio,
			    unsigned long *wait)
{
	bool rw = bio_data_dir(bio);
	unsigned long bps_wait = 0, iops_wait = 0, max_wait = 0;

	/*
 	 * Currently whole state machine of group depends on first bio
	 * queued in the group bio list. So one should not be calling
	 * this function with a different bio if there are other bios
	 * queued.
	 */
	BUG_ON(tg->service_queue.nr_queued[rw] &&
	       bio != throtl_peek_queued(&tg->service_queue.queued[rw]));

	/* If tg->bps = -1, then BW is unlimited */
	if (tg_bps_limit(tg, rw) == U64_MAX &&
	    tg_iops_limit(tg, rw) == UINT_MAX) {
		if (wait)
			*wait = 0;
		return true;
	}

	/*
	 * If previous slice expired, start a new one otherwise renew/extend
	 * existing slice to make sure it is at least throtl_slice interval
	 * long since now. New slice is started only for empty throttle group.
	 * If there is queued bio, that means there should be an active
	 * slice and it should be extended instead.
	 */
	if (throtl_slice_used(tg, rw) && !(tg->service_queue.nr_queued[rw]))
		throtl_start_new_slice(tg, rw);
	else {
		if (time_before(tg->slice_end[rw],
		    jiffies + tg->td->throtl_slice))
			throtl_extend_slice(tg, rw,
				jiffies + tg->td->throtl_slice);
	}

	if (tg_with_in_bps_limit(tg, bio, &bps_wait) &&
	    tg_with_in_iops_limit(tg, bio, &iops_wait)) {
		if (wait)
			*wait = 0;
		return true;
	}

	max_wait = max(bps_wait, iops_wait);

	if (wait)
		*wait = max_wait;

	if (time_before(tg->slice_end[rw], jiffies + max_wait))
		throtl_extend_slice(tg, rw, jiffies + max_wait);

	return false;
}