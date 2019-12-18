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
struct cache {int /*<<< orphan*/  sb; int /*<<< orphan*/  invalidate_needs_gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int CACHE_REPLACEMENT (int /*<<< orphan*/ *) ; 
#define  CACHE_REPLACEMENT_FIFO 130 
#define  CACHE_REPLACEMENT_LRU 129 
#define  CACHE_REPLACEMENT_RANDOM 128 
 int /*<<< orphan*/  invalidate_buckets_fifo (struct cache*) ; 
 int /*<<< orphan*/  invalidate_buckets_lru (struct cache*) ; 
 int /*<<< orphan*/  invalidate_buckets_random (struct cache*) ; 

__attribute__((used)) static void invalidate_buckets(struct cache *ca)
{
	BUG_ON(ca->invalidate_needs_gc);

	switch (CACHE_REPLACEMENT(&ca->sb)) {
	case CACHE_REPLACEMENT_LRU:
		invalidate_buckets_lru(ca);
		break;
	case CACHE_REPLACEMENT_FIFO:
		invalidate_buckets_fifo(ca);
		break;
	case CACHE_REPLACEMENT_RANDOM:
		invalidate_buckets_random(ca);
		break;
	}
}