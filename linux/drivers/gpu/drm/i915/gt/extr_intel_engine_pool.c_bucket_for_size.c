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
struct list_head {int dummy; } ;
struct intel_engine_pool {struct list_head* cache_list; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct list_head*) ; 
 size_t PAGE_SHIFT ; 
 int fls (size_t) ; 

__attribute__((used)) static struct list_head *
bucket_for_size(struct intel_engine_pool *pool, size_t sz)
{
	int n;

	/*
	 * Compute a power-of-two bucket, but throw everything greater than
	 * 16KiB into the same bucket: i.e. the buckets hold objects of
	 * (1 page, 2 pages, 4 pages, 8+ pages).
	 */
	n = fls(sz >> PAGE_SHIFT) - 1;
	if (n >= ARRAY_SIZE(pool->cache_list))
		n = ARRAY_SIZE(pool->cache_list) - 1;

	return &pool->cache_list[n];
}