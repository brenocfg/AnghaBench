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
struct stripe_head {size_t pd_idx; int disks; scalar_t__ qd_idx; scalar_t__ log_start; int /*<<< orphan*/  log_list; int /*<<< orphan*/  count; int /*<<< orphan*/  state; TYPE_1__* dev; scalar_t__ log_io; struct r5conf* raid_conf; } ;
struct r5l_log {scalar_t__ r5c_journal_mode; scalar_t__ last_checkpoint; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  io_list_lock; int /*<<< orphan*/  no_mem_stripes; int /*<<< orphan*/  uuid_checksum; } ;
struct r5conf {int /*<<< orphan*/  cache_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  log_checksum; int /*<<< orphan*/  page; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EAGAIN ; 
 scalar_t__ MaxSector ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ R5C_JOURNAL_MODE_WRITE_THROUGH ; 
 int /*<<< orphan*/  R5C_LOG_CRITICAL ; 
 int /*<<< orphan*/  R5_InJournal ; 
 int /*<<< orphan*/  R5_Wantwrite ; 
 int /*<<< orphan*/  STRIPE_DELAYED ; 
 int /*<<< orphan*/  STRIPE_LOG_TRAPPED ; 
 int /*<<< orphan*/  STRIPE_R5C_CACHING ; 
 int /*<<< orphan*/  STRIPE_SYNCING ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crc32c_le (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r5l_add_no_space_stripe (struct r5l_log*,struct stripe_head*) ; 
 int /*<<< orphan*/  r5l_has_free_space (struct r5l_log*,int) ; 
 int r5l_log_stripe (struct r5l_log*,struct stripe_head*,int,int) ; 
 int /*<<< orphan*/  r5l_wake_reclaim (struct r5l_log*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int r5l_write_stripe(struct r5l_log *log, struct stripe_head *sh)
{
	struct r5conf *conf = sh->raid_conf;
	int write_disks = 0;
	int data_pages, parity_pages;
	int reserve;
	int i;
	int ret = 0;
	bool wake_reclaim = false;

	if (!log)
		return -EAGAIN;
	/* Don't support stripe batch */
	if (sh->log_io || !test_bit(R5_Wantwrite, &sh->dev[sh->pd_idx].flags) ||
	    test_bit(STRIPE_SYNCING, &sh->state)) {
		/* the stripe is written to log, we start writing it to raid */
		clear_bit(STRIPE_LOG_TRAPPED, &sh->state);
		return -EAGAIN;
	}

	WARN_ON(test_bit(STRIPE_R5C_CACHING, &sh->state));

	for (i = 0; i < sh->disks; i++) {
		void *addr;

		if (!test_bit(R5_Wantwrite, &sh->dev[i].flags) ||
		    test_bit(R5_InJournal, &sh->dev[i].flags))
			continue;

		write_disks++;
		/* checksum is already calculated in last run */
		if (test_bit(STRIPE_LOG_TRAPPED, &sh->state))
			continue;
		addr = kmap_atomic(sh->dev[i].page);
		sh->dev[i].log_checksum = crc32c_le(log->uuid_checksum,
						    addr, PAGE_SIZE);
		kunmap_atomic(addr);
	}
	parity_pages = 1 + !!(sh->qd_idx >= 0);
	data_pages = write_disks - parity_pages;

	set_bit(STRIPE_LOG_TRAPPED, &sh->state);
	/*
	 * The stripe must enter state machine again to finish the write, so
	 * don't delay.
	 */
	clear_bit(STRIPE_DELAYED, &sh->state);
	atomic_inc(&sh->count);

	mutex_lock(&log->io_mutex);
	/* meta + data */
	reserve = (1 + write_disks) << (PAGE_SHIFT - 9);

	if (log->r5c_journal_mode == R5C_JOURNAL_MODE_WRITE_THROUGH) {
		if (!r5l_has_free_space(log, reserve)) {
			r5l_add_no_space_stripe(log, sh);
			wake_reclaim = true;
		} else {
			ret = r5l_log_stripe(log, sh, data_pages, parity_pages);
			if (ret) {
				spin_lock_irq(&log->io_list_lock);
				list_add_tail(&sh->log_list,
					      &log->no_mem_stripes);
				spin_unlock_irq(&log->io_list_lock);
			}
		}
	} else {  /* R5C_JOURNAL_MODE_WRITE_BACK */
		/*
		 * log space critical, do not process stripes that are
		 * not in cache yet (sh->log_start == MaxSector).
		 */
		if (test_bit(R5C_LOG_CRITICAL, &conf->cache_state) &&
		    sh->log_start == MaxSector) {
			r5l_add_no_space_stripe(log, sh);
			wake_reclaim = true;
			reserve = 0;
		} else if (!r5l_has_free_space(log, reserve)) {
			if (sh->log_start == log->last_checkpoint)
				BUG();
			else
				r5l_add_no_space_stripe(log, sh);
		} else {
			ret = r5l_log_stripe(log, sh, data_pages, parity_pages);
			if (ret) {
				spin_lock_irq(&log->io_list_lock);
				list_add_tail(&sh->log_list,
					      &log->no_mem_stripes);
				spin_unlock_irq(&log->io_list_lock);
			}
		}
	}

	mutex_unlock(&log->io_mutex);
	if (wake_reclaim)
		r5l_wake_reclaim(log, reserve);
	return 0;
}