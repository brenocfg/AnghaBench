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
struct cache {int buckets; TYPE_1__* set; } ;
struct bucket {int /*<<< orphan*/  pin; int /*<<< orphan*/  prio; } ;
struct TYPE_2__ {int /*<<< orphan*/  bucket_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ GC_MARK (struct bucket*) ; 
 scalar_t__ GC_MARK_RECLAIMABLE ; 
 scalar_t__ GC_SECTORS_USED (struct bucket*) ; 
 int /*<<< orphan*/  INITIAL_PRIO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_inc_gen (struct cache*,struct bucket*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_bcache_invalidate (struct cache*,struct bucket*) ; 

void __bch_invalidate_one_bucket(struct cache *ca, struct bucket *b)
{
	lockdep_assert_held(&ca->set->bucket_lock);
	BUG_ON(GC_MARK(b) && GC_MARK(b) != GC_MARK_RECLAIMABLE);

	if (GC_SECTORS_USED(b))
		trace_bcache_invalidate(ca, b - ca->buckets);

	bch_inc_gen(ca, b);
	b->prio = INITIAL_PRIO;
	atomic_inc(&b->pin);
}