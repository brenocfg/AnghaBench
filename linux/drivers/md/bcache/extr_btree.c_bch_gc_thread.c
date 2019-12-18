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
struct cache_set {int /*<<< orphan*/  flags; int /*<<< orphan*/  gc_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SET_IO_DISABLE ; 
 int /*<<< orphan*/  bch_btree_gc (struct cache_set*) ; 
 scalar_t__ gc_should_run (struct cache_set*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  set_gc_sectors (struct cache_set*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_kthread_stop () ; 

__attribute__((used)) static int bch_gc_thread(void *arg)
{
	struct cache_set *c = arg;

	while (1) {
		wait_event_interruptible(c->gc_wait,
			   kthread_should_stop() ||
			   test_bit(CACHE_SET_IO_DISABLE, &c->flags) ||
			   gc_should_run(c));

		if (kthread_should_stop() ||
		    test_bit(CACHE_SET_IO_DISABLE, &c->flags))
			break;

		set_gc_sectors(c);
		bch_btree_gc(c);
	}

	wait_for_kthread_stop();
	return 0;
}