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
struct cache_set {int caches_loaded; struct cache** cache_by_alloc; int /*<<< orphan*/  bucket_lock; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr_this_dev; } ;
struct cache {TYPE_2__ sb; TYPE_1__* buckets; } ;
struct bkey {int /*<<< orphan*/ * ptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CACHE_SET_IO_DISABLE ; 
 int /*<<< orphan*/  MAKE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_CACHES_PER_SET ; 
 int /*<<< orphan*/  SET_KEY_PTRS (struct bkey*,int) ; 
 long bch_bucket_alloc (struct cache*,unsigned int,int) ; 
 int /*<<< orphan*/  bch_bucket_free (struct cache_set*,struct bkey*) ; 
 int /*<<< orphan*/  bkey_init (struct bkey*) ; 
 int /*<<< orphan*/  bkey_put (struct cache_set*,struct bkey*) ; 
 int /*<<< orphan*/  bucket_to_sector (struct cache_set*,long) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int __bch_bucket_alloc_set(struct cache_set *c, unsigned int reserve,
			   struct bkey *k, int n, bool wait)
{
	int i;

	/* No allocation if CACHE_SET_IO_DISABLE bit is set */
	if (unlikely(test_bit(CACHE_SET_IO_DISABLE, &c->flags)))
		return -1;

	lockdep_assert_held(&c->bucket_lock);
	BUG_ON(!n || n > c->caches_loaded || n > MAX_CACHES_PER_SET);

	bkey_init(k);

	/* sort by free space/prio of oldest data in caches */

	for (i = 0; i < n; i++) {
		struct cache *ca = c->cache_by_alloc[i];
		long b = bch_bucket_alloc(ca, reserve, wait);

		if (b == -1)
			goto err;

		k->ptr[i] = MAKE_PTR(ca->buckets[b].gen,
				bucket_to_sector(c, b),
				ca->sb.nr_this_dev);

		SET_KEY_PTRS(k, i + 1);
	}

	return 0;
err:
	bch_bucket_free(c, k);
	bkey_put(c, k);
	return -1;
}