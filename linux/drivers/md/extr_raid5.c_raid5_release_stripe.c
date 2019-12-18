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
struct stripe_head {int hash_lock_index; int /*<<< orphan*/  count; int /*<<< orphan*/  release_list; int /*<<< orphan*/  state; struct r5conf* raid_conf; } ;
struct r5conf {int /*<<< orphan*/  device_lock; TYPE_1__* mddev; int /*<<< orphan*/  released_stripes; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  STRIPE_ON_RELEASE_LIST ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ atomic_dec_and_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  do_release_stripe (struct r5conf*,struct stripe_head*,struct list_head*) ; 
 int llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_inactive_stripe_list (struct r5conf*,struct list_head*,int) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void raid5_release_stripe(struct stripe_head *sh)
{
	struct r5conf *conf = sh->raid_conf;
	unsigned long flags;
	struct list_head list;
	int hash;
	bool wakeup;

	/* Avoid release_list until the last reference.
	 */
	if (atomic_add_unless(&sh->count, -1, 1))
		return;

	if (unlikely(!conf->mddev->thread) ||
		test_and_set_bit(STRIPE_ON_RELEASE_LIST, &sh->state))
		goto slow_path;
	wakeup = llist_add(&sh->release_list, &conf->released_stripes);
	if (wakeup)
		md_wakeup_thread(conf->mddev->thread);
	return;
slow_path:
	/* we are ok here if STRIPE_ON_RELEASE_LIST is set or not */
	if (atomic_dec_and_lock_irqsave(&sh->count, &conf->device_lock, flags)) {
		INIT_LIST_HEAD(&list);
		hash = sh->hash_lock_index;
		do_release_stripe(conf, sh, &list);
		spin_unlock_irqrestore(&conf->device_lock, flags);
		release_inactive_stripe_list(conf, &list, hash);
	}
}