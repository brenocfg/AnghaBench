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
struct stripe_head_state {scalar_t__ failed; int waiting_extra_page; scalar_t__ locked; scalar_t__ req_compute; } ;
struct stripe_head {scalar_t__ sector; int pd_idx; int qd_idx; int /*<<< orphan*/  state; struct r5dev* dev; } ;
struct r5dev {scalar_t__ page; scalar_t__ orig_page; int /*<<< orphan*/  flags; scalar_t__ towrite; } ;
struct r5conf {scalar_t__ rmw_level; TYPE_1__* mddev; int /*<<< orphan*/  cache_state; } ;
struct page {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {scalar_t__ recovery_cp; scalar_t__ queue; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ MaxSector ; 
 scalar_t__ PARITY_DISABLE_RMW ; 
 scalar_t__ PARITY_PREFER_RMW ; 
 int /*<<< orphan*/  R5C_EXTRA_PAGE_IN_USE ; 
 int /*<<< orphan*/  R5_InJournal ; 
 int /*<<< orphan*/  R5_Insync ; 
 int /*<<< orphan*/  R5_LOCKED ; 
 int /*<<< orphan*/  R5_OVERWRITE ; 
 int /*<<< orphan*/  R5_UPTODATE ; 
 int /*<<< orphan*/  R5_Wantcompute ; 
 int /*<<< orphan*/  R5_Wantread ; 
 int /*<<< orphan*/  STRIPE_BIT_DELAY ; 
 int /*<<< orphan*/  STRIPE_COMPUTE_RUN ; 
 int /*<<< orphan*/  STRIPE_DELAYED ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_PREREAD_ACTIVE ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_add_trace_msg (scalar_t__,char*,unsigned long long,int,...) ; 
 int /*<<< orphan*/  delay_towrite (struct r5conf*,struct r5dev*,struct stripe_head_state*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  r5c_use_extra_page (struct stripe_head*) ; 
 int /*<<< orphan*/  schedule_reconstruction (struct stripe_head*,struct stripe_head_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ uptodate_for_rmw (struct r5dev*) ; 

__attribute__((used)) static int handle_stripe_dirtying(struct r5conf *conf,
				  struct stripe_head *sh,
				  struct stripe_head_state *s,
				  int disks)
{
	int rmw = 0, rcw = 0, i;
	sector_t recovery_cp = conf->mddev->recovery_cp;

	/* Check whether resync is now happening or should start.
	 * If yes, then the array is dirty (after unclean shutdown or
	 * initial creation), so parity in some stripes might be inconsistent.
	 * In this case, we need to always do reconstruct-write, to ensure
	 * that in case of drive failure or read-error correction, we
	 * generate correct data from the parity.
	 */
	if (conf->rmw_level == PARITY_DISABLE_RMW ||
	    (recovery_cp < MaxSector && sh->sector >= recovery_cp &&
	     s->failed == 0)) {
		/* Calculate the real rcw later - for now make it
		 * look like rcw is cheaper
		 */
		rcw = 1; rmw = 2;
		pr_debug("force RCW rmw_level=%u, recovery_cp=%llu sh->sector=%llu\n",
			 conf->rmw_level, (unsigned long long)recovery_cp,
			 (unsigned long long)sh->sector);
	} else for (i = disks; i--; ) {
		/* would I have to read this buffer for read_modify_write */
		struct r5dev *dev = &sh->dev[i];
		if (((dev->towrite && !delay_towrite(conf, dev, s)) ||
		     i == sh->pd_idx || i == sh->qd_idx ||
		     test_bit(R5_InJournal, &dev->flags)) &&
		    !test_bit(R5_LOCKED, &dev->flags) &&
		    !(uptodate_for_rmw(dev) ||
		      test_bit(R5_Wantcompute, &dev->flags))) {
			if (test_bit(R5_Insync, &dev->flags))
				rmw++;
			else
				rmw += 2*disks;  /* cannot read it */
		}
		/* Would I have to read this buffer for reconstruct_write */
		if (!test_bit(R5_OVERWRITE, &dev->flags) &&
		    i != sh->pd_idx && i != sh->qd_idx &&
		    !test_bit(R5_LOCKED, &dev->flags) &&
		    !(test_bit(R5_UPTODATE, &dev->flags) ||
		      test_bit(R5_Wantcompute, &dev->flags))) {
			if (test_bit(R5_Insync, &dev->flags))
				rcw++;
			else
				rcw += 2*disks;
		}
	}

	pr_debug("for sector %llu state 0x%lx, rmw=%d rcw=%d\n",
		 (unsigned long long)sh->sector, sh->state, rmw, rcw);
	set_bit(STRIPE_HANDLE, &sh->state);
	if ((rmw < rcw || (rmw == rcw && conf->rmw_level == PARITY_PREFER_RMW)) && rmw > 0) {
		/* prefer read-modify-write, but need to get some data */
		if (conf->mddev->queue)
			blk_add_trace_msg(conf->mddev->queue,
					  "raid5 rmw %llu %d",
					  (unsigned long long)sh->sector, rmw);
		for (i = disks; i--; ) {
			struct r5dev *dev = &sh->dev[i];
			if (test_bit(R5_InJournal, &dev->flags) &&
			    dev->page == dev->orig_page &&
			    !test_bit(R5_LOCKED, &sh->dev[sh->pd_idx].flags)) {
				/* alloc page for prexor */
				struct page *p = alloc_page(GFP_NOIO);

				if (p) {
					dev->orig_page = p;
					continue;
				}

				/*
				 * alloc_page() failed, try use
				 * disk_info->extra_page
				 */
				if (!test_and_set_bit(R5C_EXTRA_PAGE_IN_USE,
						      &conf->cache_state)) {
					r5c_use_extra_page(sh);
					break;
				}

				/* extra_page in use, add to delayed_list */
				set_bit(STRIPE_DELAYED, &sh->state);
				s->waiting_extra_page = 1;
				return -EAGAIN;
			}
		}

		for (i = disks; i--; ) {
			struct r5dev *dev = &sh->dev[i];
			if (((dev->towrite && !delay_towrite(conf, dev, s)) ||
			     i == sh->pd_idx || i == sh->qd_idx ||
			     test_bit(R5_InJournal, &dev->flags)) &&
			    !test_bit(R5_LOCKED, &dev->flags) &&
			    !(uptodate_for_rmw(dev) ||
			      test_bit(R5_Wantcompute, &dev->flags)) &&
			    test_bit(R5_Insync, &dev->flags)) {
				if (test_bit(STRIPE_PREREAD_ACTIVE,
					     &sh->state)) {
					pr_debug("Read_old block %d for r-m-w\n",
						 i);
					set_bit(R5_LOCKED, &dev->flags);
					set_bit(R5_Wantread, &dev->flags);
					s->locked++;
				} else {
					set_bit(STRIPE_DELAYED, &sh->state);
					set_bit(STRIPE_HANDLE, &sh->state);
				}
			}
		}
	}
	if ((rcw < rmw || (rcw == rmw && conf->rmw_level != PARITY_PREFER_RMW)) && rcw > 0) {
		/* want reconstruct write, but need to get some data */
		int qread =0;
		rcw = 0;
		for (i = disks; i--; ) {
			struct r5dev *dev = &sh->dev[i];
			if (!test_bit(R5_OVERWRITE, &dev->flags) &&
			    i != sh->pd_idx && i != sh->qd_idx &&
			    !test_bit(R5_LOCKED, &dev->flags) &&
			    !(test_bit(R5_UPTODATE, &dev->flags) ||
			      test_bit(R5_Wantcompute, &dev->flags))) {
				rcw++;
				if (test_bit(R5_Insync, &dev->flags) &&
				    test_bit(STRIPE_PREREAD_ACTIVE,
					     &sh->state)) {
					pr_debug("Read_old block "
						"%d for Reconstruct\n", i);
					set_bit(R5_LOCKED, &dev->flags);
					set_bit(R5_Wantread, &dev->flags);
					s->locked++;
					qread++;
				} else {
					set_bit(STRIPE_DELAYED, &sh->state);
					set_bit(STRIPE_HANDLE, &sh->state);
				}
			}
		}
		if (rcw && conf->mddev->queue)
			blk_add_trace_msg(conf->mddev->queue, "raid5 rcw %llu %d %d %d",
					  (unsigned long long)sh->sector,
					  rcw, qread, test_bit(STRIPE_DELAYED, &sh->state));
	}

	if (rcw > disks && rmw > disks &&
	    !test_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
		set_bit(STRIPE_DELAYED, &sh->state);

	/* now if nothing is locked, and if we have enough data,
	 * we can start a write request
	 */
	/* since handle_stripe can be called at any time we need to handle the
	 * case where a compute block operation has been submitted and then a
	 * subsequent call wants to start a write request.  raid_run_ops only
	 * handles the case where compute block and reconstruct are requested
	 * simultaneously.  If this is not the case then new writes need to be
	 * held off until the compute completes.
	 */
	if ((s->req_compute || !test_bit(STRIPE_COMPUTE_RUN, &sh->state)) &&
	    (s->locked == 0 && (rcw == 0 || rmw == 0) &&
	     !test_bit(STRIPE_BIT_DELAY, &sh->state)))
		schedule_reconstruction(sh, s, rcw == 0, 0);
	return 0;
}