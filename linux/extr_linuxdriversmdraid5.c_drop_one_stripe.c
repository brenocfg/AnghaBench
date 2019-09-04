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
struct stripe_head {int /*<<< orphan*/  count; } ;
struct r5conf {int max_nr_stripes; int /*<<< orphan*/  active_stripes; int /*<<< orphan*/  slab_cache; scalar_t__ hash_locks; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int STRIPE_HASH_LOCKS_MASK ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_stripe (int /*<<< orphan*/ ,struct stripe_head*) ; 
 struct stripe_head* get_free_stripe (struct r5conf*,int) ; 
 int /*<<< orphan*/  shrink_buffers (struct stripe_head*) ; 
 int /*<<< orphan*/  spin_lock_irq (scalar_t__) ; 
 int /*<<< orphan*/  spin_unlock_irq (scalar_t__) ; 

__attribute__((used)) static int drop_one_stripe(struct r5conf *conf)
{
	struct stripe_head *sh;
	int hash = (conf->max_nr_stripes - 1) & STRIPE_HASH_LOCKS_MASK;

	spin_lock_irq(conf->hash_locks + hash);
	sh = get_free_stripe(conf, hash);
	spin_unlock_irq(conf->hash_locks + hash);
	if (!sh)
		return 0;
	BUG_ON(atomic_read(&sh->count));
	shrink_buffers(sh);
	free_stripe(conf->slab_cache, sh);
	atomic_dec(&conf->active_stripes);
	conf->max_nr_stripes--;
	return 1;
}