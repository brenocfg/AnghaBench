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
struct TYPE_2__ {int nbuckets; int first_bucket; } ;
struct cache {int invalidate_needs_gc; int /*<<< orphan*/  set; TYPE_1__ sb; struct bucket* buckets; int /*<<< orphan*/  free_inc; } ;
struct bucket {int dummy; } ;
typedef  int /*<<< orphan*/  n ;

/* Variables and functions */
 scalar_t__ bch_can_invalidate_bucket (struct cache*,struct bucket*) ; 
 int /*<<< orphan*/  bch_invalidate_one_bucket (struct cache*,struct bucket*) ; 
 int /*<<< orphan*/  fifo_full (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_random_bytes (size_t*,int) ; 
 int /*<<< orphan*/  wake_up_gc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void invalidate_buckets_random(struct cache *ca)
{
	struct bucket *b;
	size_t checked = 0;

	while (!fifo_full(&ca->free_inc)) {
		size_t n;

		get_random_bytes(&n, sizeof(n));

		n %= (size_t) (ca->sb.nbuckets - ca->sb.first_bucket);
		n += ca->sb.first_bucket;

		b = ca->buckets + n;

		if (bch_can_invalidate_bucket(ca, b))
			bch_invalidate_one_bucket(ca, b);

		if (++checked >= ca->sb.nbuckets / 2) {
			ca->invalidate_needs_gc = 1;
			wake_up_gc(ca->set);
			return;
		}
	}
}