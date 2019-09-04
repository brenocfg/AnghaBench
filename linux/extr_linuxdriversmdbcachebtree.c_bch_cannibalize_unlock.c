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
struct cache_set {int /*<<< orphan*/  btree_cache_wait; int /*<<< orphan*/ * btree_cache_alloc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bch_cannibalize_unlock(struct cache_set *c)
{
	if (c->btree_cache_alloc_lock == current) {
		c->btree_cache_alloc_lock = NULL;
		wake_up(&c->btree_cache_wait);
	}
}