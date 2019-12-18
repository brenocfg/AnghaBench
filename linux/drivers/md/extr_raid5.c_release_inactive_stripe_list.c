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
struct r5conf {TYPE_1__* mddev; scalar_t__ retry_read_aligned; int /*<<< orphan*/  wait_for_quiescent; int /*<<< orphan*/  active_stripes; int /*<<< orphan*/  wait_for_stripe; scalar_t__ hash_locks; struct list_head* inactive_list; int /*<<< orphan*/  empty_inactive_list_nr; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int NR_STRIPE_HASH_LOCKS ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_empty_careful (struct list_head*) ; 
 int /*<<< orphan*/  list_splice_tail_init (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_inactive_stripe_list(struct r5conf *conf,
					 struct list_head *temp_inactive_list,
					 int hash)
{
	int size;
	bool do_wakeup = false;
	unsigned long flags;

	if (hash == NR_STRIPE_HASH_LOCKS) {
		size = NR_STRIPE_HASH_LOCKS;
		hash = NR_STRIPE_HASH_LOCKS - 1;
	} else
		size = 1;
	while (size) {
		struct list_head *list = &temp_inactive_list[size - 1];

		/*
		 * We don't hold any lock here yet, raid5_get_active_stripe() might
		 * remove stripes from the list
		 */
		if (!list_empty_careful(list)) {
			spin_lock_irqsave(conf->hash_locks + hash, flags);
			if (list_empty(conf->inactive_list + hash) &&
			    !list_empty(list))
				atomic_dec(&conf->empty_inactive_list_nr);
			list_splice_tail_init(list, conf->inactive_list + hash);
			do_wakeup = true;
			spin_unlock_irqrestore(conf->hash_locks + hash, flags);
		}
		size--;
		hash--;
	}

	if (do_wakeup) {
		wake_up(&conf->wait_for_stripe);
		if (atomic_read(&conf->active_stripes) == 0)
			wake_up(&conf->wait_for_quiescent);
		if (conf->retry_read_aligned)
			md_wakeup_thread(conf->mddev->thread);
	}
}