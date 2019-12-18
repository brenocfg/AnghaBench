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
struct r5l_log {int /*<<< orphan*/  big_stripe_tree; } ;
struct r5conf {struct r5l_log* log; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  r5c_tree_index (struct r5conf*,int /*<<< orphan*/ ) ; 
 void* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 

bool r5c_big_stripe_cached(struct r5conf *conf, sector_t sect)
{
	struct r5l_log *log = conf->log;
	sector_t tree_index;
	void *slot;

	if (!log)
		return false;

	WARN_ON_ONCE(!rcu_read_lock_held());
	tree_index = r5c_tree_index(conf, sect);
	slot = radix_tree_lookup(&log->big_stripe_tree, tree_index);
	return slot != NULL;
}