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
struct stripe_head_state {scalar_t__ injournal; scalar_t__ written; int /*<<< orphan*/  ops_request; scalar_t__ failed; } ;
struct stripe_head {int /*<<< orphan*/  state; struct r5dev* dev; int /*<<< orphan*/  sector; } ;
struct r5l_log {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  big_stripe_tree; } ;
struct r5dev {int /*<<< orphan*/  flags; scalar_t__ towrite; } ;
struct r5conf {int /*<<< orphan*/  r5c_cached_partial_stripes; struct r5l_log* log; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 uintptr_t R5C_RADIX_COUNT_SHIFT ; 
 int /*<<< orphan*/  R5_InJournal ; 
 int /*<<< orphan*/  R5_LOCKED ; 
 int /*<<< orphan*/  R5_OVERWRITE ; 
 int /*<<< orphan*/  R5_Wantdrain ; 
 int /*<<< orphan*/  R5_Wantwrite ; 
 int /*<<< orphan*/  STRIPE_LOG_TRAPPED ; 
 int /*<<< orphan*/  STRIPE_OP_BIODRAIN ; 
 int /*<<< orphan*/  STRIPE_R5C_CACHING ; 
 int /*<<< orphan*/  STRIPE_R5C_FULL_STRIPE ; 
 int /*<<< orphan*/  STRIPE_R5C_PARTIAL_STRIPE ; 
 int /*<<< orphan*/  STRIPE_SYNCING ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r5c_is_writeback (struct r5l_log*) ; 
 int /*<<< orphan*/  r5c_make_stripe_write_out (struct stripe_head*) ; 
 int /*<<< orphan*/  r5c_tree_index (struct r5conf*,int /*<<< orphan*/ ) ; 
 scalar_t__ radix_tree_deref_slot_protected (void**,int /*<<< orphan*/ *) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 void** radix_tree_lookup_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_replace_slot (int /*<<< orphan*/ *,void**,void*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int r5c_try_caching_write(struct r5conf *conf,
			  struct stripe_head *sh,
			  struct stripe_head_state *s,
			  int disks)
{
	struct r5l_log *log = conf->log;
	int i;
	struct r5dev *dev;
	int to_cache = 0;
	void **pslot;
	sector_t tree_index;
	int ret;
	uintptr_t refcount;

	BUG_ON(!r5c_is_writeback(log));

	if (!test_bit(STRIPE_R5C_CACHING, &sh->state)) {
		/*
		 * There are two different scenarios here:
		 *  1. The stripe has some data cached, and it is sent to
		 *     write-out phase for reclaim
		 *  2. The stripe is clean, and this is the first write
		 *
		 * For 1, return -EAGAIN, so we continue with
		 * handle_stripe_dirtying().
		 *
		 * For 2, set STRIPE_R5C_CACHING and continue with caching
		 * write.
		 */

		/* case 1: anything injournal or anything in written */
		if (s->injournal > 0 || s->written > 0)
			return -EAGAIN;
		/* case 2 */
		set_bit(STRIPE_R5C_CACHING, &sh->state);
	}

	/*
	 * When run in degraded mode, array is set to write-through mode.
	 * This check helps drain pending write safely in the transition to
	 * write-through mode.
	 *
	 * When a stripe is syncing, the write is also handled in write
	 * through mode.
	 */
	if (s->failed || test_bit(STRIPE_SYNCING, &sh->state)) {
		r5c_make_stripe_write_out(sh);
		return -EAGAIN;
	}

	for (i = disks; i--; ) {
		dev = &sh->dev[i];
		/* if non-overwrite, use writing-out phase */
		if (dev->towrite && !test_bit(R5_OVERWRITE, &dev->flags) &&
		    !test_bit(R5_InJournal, &dev->flags)) {
			r5c_make_stripe_write_out(sh);
			return -EAGAIN;
		}
	}

	/* if the stripe is not counted in big_stripe_tree, add it now */
	if (!test_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state) &&
	    !test_bit(STRIPE_R5C_FULL_STRIPE, &sh->state)) {
		tree_index = r5c_tree_index(conf, sh->sector);
		spin_lock(&log->tree_lock);
		pslot = radix_tree_lookup_slot(&log->big_stripe_tree,
					       tree_index);
		if (pslot) {
			refcount = (uintptr_t)radix_tree_deref_slot_protected(
				pslot, &log->tree_lock) >>
				R5C_RADIX_COUNT_SHIFT;
			radix_tree_replace_slot(
				&log->big_stripe_tree, pslot,
				(void *)((refcount + 1) << R5C_RADIX_COUNT_SHIFT));
		} else {
			/*
			 * this radix_tree_insert can fail safely, so no
			 * need to call radix_tree_preload()
			 */
			ret = radix_tree_insert(
				&log->big_stripe_tree, tree_index,
				(void *)(1 << R5C_RADIX_COUNT_SHIFT));
			if (ret) {
				spin_unlock(&log->tree_lock);
				r5c_make_stripe_write_out(sh);
				return -EAGAIN;
			}
		}
		spin_unlock(&log->tree_lock);

		/*
		 * set STRIPE_R5C_PARTIAL_STRIPE, this shows the stripe is
		 * counted in the radix tree
		 */
		set_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state);
		atomic_inc(&conf->r5c_cached_partial_stripes);
	}

	for (i = disks; i--; ) {
		dev = &sh->dev[i];
		if (dev->towrite) {
			set_bit(R5_Wantwrite, &dev->flags);
			set_bit(R5_Wantdrain, &dev->flags);
			set_bit(R5_LOCKED, &dev->flags);
			to_cache++;
		}
	}

	if (to_cache) {
		set_bit(STRIPE_OP_BIODRAIN, &s->ops_request);
		/*
		 * set STRIPE_LOG_TRAPPED, which triggers r5c_cache_data()
		 * in ops_run_io(). STRIPE_LOG_TRAPPED will be cleared in
		 * r5c_handle_data_cached()
		 */
		set_bit(STRIPE_LOG_TRAPPED, &sh->state);
	}

	return 0;
}