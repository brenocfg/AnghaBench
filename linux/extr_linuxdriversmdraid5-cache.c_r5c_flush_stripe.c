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
struct stripe_head {int /*<<< orphan*/  state; int /*<<< orphan*/  count; int /*<<< orphan*/  lru; } ;
struct r5conf {int /*<<< orphan*/  r5c_flushing_full_stripes; int /*<<< orphan*/  r5c_flushing_partial_stripes; int /*<<< orphan*/  active_stripes; int /*<<< orphan*/  device_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_ON_RELEASE_LIST ; 
 int /*<<< orphan*/  STRIPE_R5C_CACHING ; 
 int /*<<< orphan*/  STRIPE_R5C_PARTIAL_STRIPE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r5c_make_stripe_write_out (struct stripe_head*) ; 
 int /*<<< orphan*/  raid5_release_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r5c_flush_stripe(struct r5conf *conf, struct stripe_head *sh)
{
	BUG_ON(list_empty(&sh->lru));
	BUG_ON(!test_bit(STRIPE_R5C_CACHING, &sh->state));
	BUG_ON(test_bit(STRIPE_HANDLE, &sh->state));

	/*
	 * The stripe is not ON_RELEASE_LIST, so it is safe to call
	 * raid5_release_stripe() while holding conf->device_lock
	 */
	BUG_ON(test_bit(STRIPE_ON_RELEASE_LIST, &sh->state));
	lockdep_assert_held(&conf->device_lock);

	list_del_init(&sh->lru);
	atomic_inc(&sh->count);

	set_bit(STRIPE_HANDLE, &sh->state);
	atomic_inc(&conf->active_stripes);
	r5c_make_stripe_write_out(sh);

	if (test_bit(STRIPE_R5C_PARTIAL_STRIPE, &sh->state))
		atomic_inc(&conf->r5c_flushing_partial_stripes);
	else
		atomic_inc(&conf->r5c_flushing_full_stripes);
	raid5_release_stripe(sh);
}