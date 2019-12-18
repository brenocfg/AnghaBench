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
struct stripe_head {int disks; scalar_t__ bm_seq; size_t pd_idx; int /*<<< orphan*/  lru; int /*<<< orphan*/  state; TYPE_2__* dev; } ;
struct list_head {int dummy; } ;
struct r5conf {scalar_t__ seq_write; scalar_t__ worker_cnt_per_group; int raid_disks; int max_degraded; struct list_head r5c_partial_stripe_list; struct list_head r5c_full_stripe_list; int /*<<< orphan*/  r5c_cached_partial_stripes; int /*<<< orphan*/  r5c_cached_full_stripes; int /*<<< orphan*/  log; int /*<<< orphan*/  active_stripes; TYPE_1__* mddev; int /*<<< orphan*/  preread_active_stripes; struct list_head handle_list; struct list_head loprio_list; struct list_head bitmap_list; struct list_head delayed_list; scalar_t__ quiesce; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IO_THRESHOLD ; 
 int /*<<< orphan*/  R5_InJournal ; 
 int /*<<< orphan*/  STRIPE_BIT_DELAY ; 
 int /*<<< orphan*/  STRIPE_DELAYED ; 
 int /*<<< orphan*/  STRIPE_EXPANDING ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_PREREAD_ACTIVE ; 
 int /*<<< orphan*/  STRIPE_R5C_CACHING ; 
 int /*<<< orphan*/  STRIPE_R5C_FULL_STRIPE ; 
 int /*<<< orphan*/  STRIPE_R5C_PARTIAL_STRIPE ; 
 int /*<<< orphan*/  STRIPE_SYNC_REQUESTED ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5c_check_cached_full_stripe (struct r5conf*) ; 
 scalar_t__ r5c_is_writeback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5c_make_stripe_write_out (struct stripe_head*) ; 
 int /*<<< orphan*/  raid5_wakeup_stripe_thread (struct stripe_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stripe_is_lowprio (struct stripe_head*) ; 
 int stripe_operations_active (struct stripe_head*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_release_stripe(struct r5conf *conf, struct stripe_head *sh,
			      struct list_head *temp_inactive_list)
{
	int i;
	int injournal = 0;	/* number of date pages with R5_InJournal */

	BUG_ON(!list_empty(&sh->lru));
	BUG_ON(atomic_read(&conf->active_stripes)==0);

	if (r5c_is_writeback(conf->log))
		for (i = sh->disks; i--; )
			if (test_bit(R5_InJournal, &sh->dev[i].flags))
				injournal++;
	/*
	 * In the following cases, the stripe cannot be released to cached
	 * lists. Therefore, we make the stripe write out and set
	 * STRIPE_HANDLE:
	 *   1. when quiesce in r5c write back;
	 *   2. when resync is requested fot the stripe.
	 */
	if (test_bit(STRIPE_SYNC_REQUESTED, &sh->state) ||
	    (conf->quiesce && r5c_is_writeback(conf->log) &&
	     !test_bit(STRIPE_HANDLE, &sh->state) && injournal != 0)) {
		if (test_bit(STRIPE_R5C_CACHING, &sh->state))
			r5c_make_stripe_write_out(sh);
		set_bit(STRIPE_HANDLE, &sh->state);
	}

	if (test_bit(STRIPE_HANDLE, &sh->state)) {
		if (test_bit(STRIPE_DELAYED, &sh->state) &&
		    !test_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
			list_add_tail(&sh->lru, &conf->delayed_list);
		else if (test_bit(STRIPE_BIT_DELAY, &sh->state) &&
			   sh->bm_seq - conf->seq_write > 0)
			list_add_tail(&sh->lru, &conf->bitmap_list);
		else {
			clear_bit(STRIPE_DELAYED, &sh->state);
			clear_bit(STRIPE_BIT_DELAY, &sh->state);
			if (conf->worker_cnt_per_group == 0) {
				if (stripe_is_lowprio(sh))
					list_add_tail(&sh->lru,
							&conf->loprio_list);
				else
					list_add_tail(&sh->lru,
							&conf->handle_list);
			} else {
				raid5_wakeup_stripe_thread(sh);
				return;
			}
		}
		md_wakeup_thread(conf->mddev->thread);
	} else {
		BUG_ON(stripe_operations_active(sh));
		if (test_and_clear_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
			if (atomic_dec_return(&conf->preread_active_stripes)
			    < IO_THRESHOLD)
				md_wakeup_thread(conf->mddev->thread);
		atomic_dec(&conf->active_stripes);
		if (!test_bit(STRIPE_EXPANDING, &sh->state)) {
			if (!r5c_is_writeback(conf->log))
				list_add_tail(&sh->lru, temp_inactive_list);
			else {
				WARN_ON(test_bit(R5_InJournal, &sh->dev[sh->pd_idx].flags));
				if (injournal == 0)
					list_add_tail(&sh->lru, temp_inactive_list);
				else if (injournal == conf->raid_disks - conf->max_degraded) {
					/* full stripe */
					if (!test_and_set_bit(STRIPE_R5C_FULL_STRIPE, &sh->state))
						atomic_inc(&conf->r5c_cached_full_stripes);
					if (test_and_clear_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state))
						atomic_dec(&conf->r5c_cached_partial_stripes);
					list_add_tail(&sh->lru, &conf->r5c_full_stripe_list);
					r5c_check_cached_full_stripe(conf);
				} else
					/*
					 * STRIPE_R5C_PARTIAL_STRIPE is set in
					 * r5c_try_caching_write(). No need to
					 * set it again.
					 */
					list_add_tail(&sh->lru, &conf->r5c_partial_stripe_list);
			}
		}
	}
}