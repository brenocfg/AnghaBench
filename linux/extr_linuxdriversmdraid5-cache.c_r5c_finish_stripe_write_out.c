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
struct stripe_head_state {scalar_t__ injournal; } ;
struct stripe_head {size_t pd_idx; int disks; int /*<<< orphan*/  state; int /*<<< orphan*/  sector; int /*<<< orphan*/  log_start; int /*<<< orphan*/  r5c; TYPE_1__* dev; } ;
struct r5l_log {scalar_t__ r5c_journal_mode; int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  big_stripe_tree; int /*<<< orphan*/  stripe_in_journal_count; int /*<<< orphan*/  stripe_in_journal_lock; } ;
struct r5conf {int /*<<< orphan*/  r5c_cached_full_stripes; int /*<<< orphan*/  r5c_flushing_full_stripes; int /*<<< orphan*/  r5c_cached_partial_stripes; int /*<<< orphan*/  r5c_flushing_partial_stripes; int /*<<< orphan*/  wait_for_overlap; TYPE_2__* mddev; int /*<<< orphan*/  pending_full_writes; struct r5l_log* log; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  thread; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MaxSector ; 
 scalar_t__ R5C_JOURNAL_MODE_WRITE_THROUGH ; 
 uintptr_t R5C_RADIX_COUNT_SHIFT ; 
 int /*<<< orphan*/  R5_InJournal ; 
 int /*<<< orphan*/  R5_Overlap ; 
 int /*<<< orphan*/  STRIPE_FULL_WRITE ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_R5C_CACHING ; 
 int /*<<< orphan*/  STRIPE_R5C_FULL_STRIPE ; 
 int /*<<< orphan*/  STRIPE_R5C_PARTIAL_STRIPE ; 
 int /*<<< orphan*/  STRIPE_SYNC_REQUESTED ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5c_tree_index (struct r5conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5c_update_log_state (struct r5l_log*) ; 
 int /*<<< orphan*/  r5l_append_flush_payload (struct r5l_log*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ radix_tree_deref_slot_protected (void**,int /*<<< orphan*/ *) ; 
 void** radix_tree_lookup_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_replace_slot (int /*<<< orphan*/ *,void**,void*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void r5c_finish_stripe_write_out(struct r5conf *conf,
				 struct stripe_head *sh,
				 struct stripe_head_state *s)
{
	struct r5l_log *log = conf->log;
	int i;
	int do_wakeup = 0;
	sector_t tree_index;
	void **pslot;
	uintptr_t refcount;

	if (!log || !test_bit(R5_InJournal, &sh->dev[sh->pd_idx].flags))
		return;

	WARN_ON(test_bit(STRIPE_R5C_CACHING, &sh->state));
	clear_bit(R5_InJournal, &sh->dev[sh->pd_idx].flags);

	if (log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_THROUGH)
		return;

	for (i = sh->disks; i--; ) {
		clear_bit(R5_InJournal, &sh->dev[i].flags);
		if (test_and_clear_bit(R5_Overlap, &sh->dev[i].flags))
			do_wakeup = 1;
	}

	/*
	 * analyse_stripe() runs before r5c_finish_stripe_write_out(),
	 * We updated R5_InJournal, so we also update s->injournal.
	 */
	s->injournal = 0;

	if (test_and_clear_bit(STRIPE_FULL_WRITE, &sh->state))
		if (atomic_dec_and_test(&conf->pending_full_writes))
			md_wakeup_thread(conf->mddev->thread);

	if (do_wakeup)
		wake_up(&conf->wait_for_overlap);

	spin_lock_irq(&log->stripe_in_journal_lock);
	list_del_init(&sh->r5c);
	spin_unlock_irq(&log->stripe_in_journal_lock);
	sh->log_start = MaxSector;

	atomic_dec(&log->stripe_in_journal_count);
	r5c_update_log_state(log);

	/* stop counting this stripe in big_stripe_tree */
	if (test_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state) ||
	    test_bit(STRIPE_R5C_FULL_STRIPE, &sh->state)) {
		tree_index = r5c_tree_index(conf, sh->sector);
		spin_lock(&log->tree_lock);
		pslot = radix_tree_lookup_slot(&log->big_stripe_tree,
					       tree_index);
		BUG_ON(pslot == NULL);
		refcount = (uintptr_t)radix_tree_deref_slot_protected(
			pslot, &log->tree_lock) >>
			R5C_RADIX_COUNT_SHIFT;
		if (refcount == 1)
			radix_tree_delete(&log->big_stripe_tree, tree_index);
		else
			radix_tree_replace_slot(
				&log->big_stripe_tree, pslot,
				(void *)((refcount - 1) << R5C_RADIX_COUNT_SHIFT));
		spin_unlock(&log->tree_lock);
	}

	if (test_and_clear_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state)) {
		BUG_ON(atomic_read(&conf->r5c_cached_partial_stripes) == 0);
		atomic_dec(&conf->r5c_flushing_partial_stripes);
		atomic_dec(&conf->r5c_cached_partial_stripes);
	}

	if (test_and_clear_bit(STRIPE_R5C_FULL_STRIPE, &sh->state)) {
		BUG_ON(atomic_read(&conf->r5c_cached_full_stripes) == 0);
		atomic_dec(&conf->r5c_flushing_full_stripes);
		atomic_dec(&conf->r5c_cached_full_stripes);
	}

	r5l_append_flush_payload(log, sh->sector);
	/* stripe is flused to raid disks, we can do resync now */
	if (test_bit(STRIPE_SYNC_REQUESTED, &sh->state))
		set_bit(STRIPE_HANDLE, &sh->state);
}