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
struct TYPE_2__ {scalar_t__ first_bucket; scalar_t__ nbuckets; } ;
struct cache {scalar_t__ fifo_last_bucket; int invalidate_needs_gc; int /*<<< orphan*/  set; TYPE_1__ sb; struct bucket* buckets; int /*<<< orphan*/  free_inc; } ;
struct bucket {int dummy; } ;

/* Variables and functions */
 scalar_t__ bch_can_invalidate_bucket (struct cache*,struct bucket*) ; 
 int /*<<< orphan*/  bch_invalidate_one_bucket (struct cache*,struct bucket*) ; 
 int /*<<< orphan*/  fifo_full (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_gc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void invalidate_buckets_fifo(struct cache *ca)
{
	struct bucket *b;
	size_t checked = 0;

	while (!fifo_full(&ca->free_inc)) {
		if (ca->fifo_last_bucket <  ca->sb.first_bucket ||
		    ca->fifo_last_bucket >= ca->sb.nbuckets)
			ca->fifo_last_bucket = ca->sb.first_bucket;

		b = ca->buckets + ca->fifo_last_bucket++;

		if (bch_can_invalidate_bucket(ca, b))
			bch_invalidate_one_bucket(ca, b);

		if (++checked >= ca->sb.nbuckets) {
			ca->invalidate_needs_gc = 1;
			wake_up_gc(ca->set);
			return;
		}
	}
}