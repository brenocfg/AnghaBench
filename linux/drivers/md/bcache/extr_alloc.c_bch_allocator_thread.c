#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bucket_size; } ;
struct cache {int /*<<< orphan*/  free_inc; TYPE_2__* set; int /*<<< orphan*/  invalidate_needs_gc; TYPE_1__ sb; int /*<<< orphan*/  bdev; scalar_t__ discard; } ;
struct TYPE_4__ {int /*<<< orphan*/  sb; int /*<<< orphan*/  prio_blocked; scalar_t__ gc_mark_valid; int /*<<< orphan*/  bucket_wait; int /*<<< orphan*/  btree_cache_wait; int /*<<< orphan*/  bucket_lock; } ;

/* Variables and functions */
 scalar_t__ CACHE_SYNC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  allocator_wait (struct cache*,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int bch_allocator_push (struct cache*,long) ; 
 int /*<<< orphan*/  bch_prio_write (struct cache*) ; 
 int /*<<< orphan*/  blkdev_issue_discard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bucket_to_sector (TYPE_2__*,long) ; 
 int /*<<< orphan*/  fifo_full (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fifo_pop (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  invalidate_buckets (struct cache*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_kthread_stop () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bch_allocator_thread(void *arg)
{
	struct cache *ca = arg;

	mutex_lock(&ca->set->bucket_lock);

	while (1) {
		/*
		 * First, we pull buckets off of the unused and free_inc lists,
		 * possibly issue discards to them, then we add the bucket to
		 * the free list:
		 */
		while (1) {
			long bucket;

			if (!fifo_pop(&ca->free_inc, bucket))
				break;

			if (ca->discard) {
				mutex_unlock(&ca->set->bucket_lock);
				blkdev_issue_discard(ca->bdev,
					bucket_to_sector(ca->set, bucket),
					ca->sb.bucket_size, GFP_KERNEL, 0);
				mutex_lock(&ca->set->bucket_lock);
			}

			allocator_wait(ca, bch_allocator_push(ca, bucket));
			wake_up(&ca->set->btree_cache_wait);
			wake_up(&ca->set->bucket_wait);
		}

		/*
		 * We've run out of free buckets, we need to find some buckets
		 * we can invalidate. First, invalidate them in memory and add
		 * them to the free_inc list:
		 */

retry_invalidate:
		allocator_wait(ca, ca->set->gc_mark_valid &&
			       !ca->invalidate_needs_gc);
		invalidate_buckets(ca);

		/*
		 * Now, we write their new gens to disk so we can start writing
		 * new stuff to them:
		 */
		allocator_wait(ca, !atomic_read(&ca->set->prio_blocked));
		if (CACHE_SYNC(&ca->set->sb)) {
			/*
			 * This could deadlock if an allocation with a btree
			 * node locked ever blocked - having the btree node
			 * locked would block garbage collection, but here we're
			 * waiting on garbage collection before we invalidate
			 * and free anything.
			 *
			 * But this should be safe since the btree code always
			 * uses btree_check_reserve() before allocating now, and
			 * if it fails it blocks without btree nodes locked.
			 */
			if (!fifo_full(&ca->free_inc))
				goto retry_invalidate;

			bch_prio_write(ca);
		}
	}
out:
	wait_for_kthread_stop();
	return 0;
}