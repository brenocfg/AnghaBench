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
struct stripe_head {int hash_lock_index; } ;
struct r5worker {int dummy; } ;
struct r5conf {int /*<<< orphan*/  device_lock; int /*<<< orphan*/  log; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int MAX_STRIPE_BATCH ; 
 int NR_STRIPE_HASH_LOCKS ; 
 struct stripe_head* __get_priority_stripe (struct r5conf*,int) ; 
 int /*<<< orphan*/  __release_stripe (struct r5conf*,struct stripe_head*,struct list_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  handle_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  log_flush_stripe_to_raid (struct r5conf*) ; 
 int /*<<< orphan*/  log_write_stripe_run (struct r5conf*) ; 
 int /*<<< orphan*/  r5l_flush_stripe_to_raid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_inactive_stripe_list (struct r5conf*,struct list_head*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_active_stripes(struct r5conf *conf, int group,
				 struct r5worker *worker,
				 struct list_head *temp_inactive_list)
{
	struct stripe_head *batch[MAX_STRIPE_BATCH], *sh;
	int i, batch_size = 0, hash;
	bool release_inactive = false;

	while (batch_size < MAX_STRIPE_BATCH &&
			(sh = __get_priority_stripe(conf, group)) != NULL)
		batch[batch_size++] = sh;

	if (batch_size == 0) {
		for (i = 0; i < NR_STRIPE_HASH_LOCKS; i++)
			if (!list_empty(temp_inactive_list + i))
				break;
		if (i == NR_STRIPE_HASH_LOCKS) {
			spin_unlock_irq(&conf->device_lock);
			log_flush_stripe_to_raid(conf);
			spin_lock_irq(&conf->device_lock);
			return batch_size;
		}
		release_inactive = true;
	}
	spin_unlock_irq(&conf->device_lock);

	release_inactive_stripe_list(conf, temp_inactive_list,
				     NR_STRIPE_HASH_LOCKS);

	r5l_flush_stripe_to_raid(conf->log);
	if (release_inactive) {
		spin_lock_irq(&conf->device_lock);
		return 0;
	}

	for (i = 0; i < batch_size; i++)
		handle_stripe(batch[i]);
	log_write_stripe_run(conf);

	cond_resched();

	spin_lock_irq(&conf->device_lock);
	for (i = 0; i < batch_size; i++) {
		hash = batch[i]->hash_lock_index;
		__release_stripe(conf, batch[i], &temp_inactive_list[hash]);
	}
	return batch_size;
}