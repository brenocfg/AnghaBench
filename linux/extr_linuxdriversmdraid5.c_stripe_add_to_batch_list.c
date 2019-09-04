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
struct stripe_head {int pd_idx; int qd_idx; int bm_seq; int /*<<< orphan*/  count; struct stripe_head* batch_head; int /*<<< orphan*/  state; int /*<<< orphan*/  batch_lock; int /*<<< orphan*/  batch_list; TYPE_2__* dev; TYPE_1__* group; int /*<<< orphan*/  lru; scalar_t__ sector; } ;
struct r5conf {TYPE_3__* mddev; int /*<<< orphan*/  preread_active_stripes; scalar_t__ hash_locks; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  empty_inactive_list_nr; int /*<<< orphan*/ * inactive_list; int /*<<< orphan*/  active_stripes; int /*<<< orphan*/  generation; int /*<<< orphan*/  chunk_sectors; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_8__ {scalar_t__ bi_opf; } ;
struct TYPE_7__ {int /*<<< orphan*/  thread; } ;
struct TYPE_6__ {TYPE_4__* towrite; } ;
struct TYPE_5__ {int /*<<< orphan*/  stripes_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IO_THRESHOLD ; 
 int /*<<< orphan*/  STRIPE_BIT_DELAY ; 
 int /*<<< orphan*/  STRIPE_EXPANDING ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_PREREAD_ACTIVE ; 
 scalar_t__ STRIPE_SECTORS ; 
 struct stripe_head* __find_stripe (struct r5conf*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_op (TYPE_4__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_two_stripes (struct stripe_head*,struct stripe_head*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid5_release_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  sector_div (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (scalar_t__) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (scalar_t__) ; 
 int /*<<< orphan*/  stripe_can_batch (struct stripe_head*) ; 
 int stripe_hash_locks_hash (scalar_t__) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_two_stripes (struct stripe_head*,struct stripe_head*) ; 

__attribute__((used)) static void stripe_add_to_batch_list(struct r5conf *conf, struct stripe_head *sh)
{
	struct stripe_head *head;
	sector_t head_sector, tmp_sec;
	int hash;
	int dd_idx;
	int inc_empty_inactive_list_flag;

	/* Don't cross chunks, so stripe pd_idx/qd_idx is the same */
	tmp_sec = sh->sector;
	if (!sector_div(tmp_sec, conf->chunk_sectors))
		return;
	head_sector = sh->sector - STRIPE_SECTORS;

	hash = stripe_hash_locks_hash(head_sector);
	spin_lock_irq(conf->hash_locks + hash);
	head = __find_stripe(conf, head_sector, conf->generation);
	if (head && !atomic_inc_not_zero(&head->count)) {
		spin_lock(&conf->device_lock);
		if (!atomic_read(&head->count)) {
			if (!test_bit(STRIPE_HANDLE, &head->state))
				atomic_inc(&conf->active_stripes);
			BUG_ON(list_empty(&head->lru) &&
			       !test_bit(STRIPE_EXPANDING, &head->state));
			inc_empty_inactive_list_flag = 0;
			if (!list_empty(conf->inactive_list + hash))
				inc_empty_inactive_list_flag = 1;
			list_del_init(&head->lru);
			if (list_empty(conf->inactive_list + hash) && inc_empty_inactive_list_flag)
				atomic_inc(&conf->empty_inactive_list_nr);
			if (head->group) {
				head->group->stripes_cnt--;
				head->group = NULL;
			}
		}
		atomic_inc(&head->count);
		spin_unlock(&conf->device_lock);
	}
	spin_unlock_irq(conf->hash_locks + hash);

	if (!head)
		return;
	if (!stripe_can_batch(head))
		goto out;

	lock_two_stripes(head, sh);
	/* clear_batch_ready clear the flag */
	if (!stripe_can_batch(head) || !stripe_can_batch(sh))
		goto unlock_out;

	if (sh->batch_head)
		goto unlock_out;

	dd_idx = 0;
	while (dd_idx == sh->pd_idx || dd_idx == sh->qd_idx)
		dd_idx++;
	if (head->dev[dd_idx].towrite->bi_opf != sh->dev[dd_idx].towrite->bi_opf ||
	    bio_op(head->dev[dd_idx].towrite) != bio_op(sh->dev[dd_idx].towrite))
		goto unlock_out;

	if (head->batch_head) {
		spin_lock(&head->batch_head->batch_lock);
		/* This batch list is already running */
		if (!stripe_can_batch(head)) {
			spin_unlock(&head->batch_head->batch_lock);
			goto unlock_out;
		}
		/*
		 * We must assign batch_head of this stripe within the
		 * batch_lock, otherwise clear_batch_ready of batch head
		 * stripe could clear BATCH_READY bit of this stripe and
		 * this stripe->batch_head doesn't get assigned, which
		 * could confuse clear_batch_ready for this stripe
		 */
		sh->batch_head = head->batch_head;

		/*
		 * at this point, head's BATCH_READY could be cleared, but we
		 * can still add the stripe to batch list
		 */
		list_add(&sh->batch_list, &head->batch_list);
		spin_unlock(&head->batch_head->batch_lock);
	} else {
		head->batch_head = head;
		sh->batch_head = head->batch_head;
		spin_lock(&head->batch_lock);
		list_add_tail(&sh->batch_list, &head->batch_list);
		spin_unlock(&head->batch_lock);
	}

	if (test_and_clear_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
		if (atomic_dec_return(&conf->preread_active_stripes)
		    < IO_THRESHOLD)
			md_wakeup_thread(conf->mddev->thread);

	if (test_and_clear_bit(STRIPE_BIT_DELAY, &sh->state)) {
		int seq = sh->bm_seq;
		if (test_bit(STRIPE_BIT_DELAY, &sh->batch_head->state) &&
		    sh->batch_head->bm_seq > seq)
			seq = sh->batch_head->bm_seq;
		set_bit(STRIPE_BIT_DELAY, &sh->batch_head->state);
		sh->batch_head->bm_seq = seq;
	}

	atomic_inc(&sh->count);
unlock_out:
	unlock_two_stripes(head, sh);
out:
	raid5_release_stripe(head);
}