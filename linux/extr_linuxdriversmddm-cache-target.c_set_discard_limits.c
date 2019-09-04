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
struct queue_limits {int discard_granularity; int /*<<< orphan*/  max_discard_sectors; } ;
struct cache {int discard_block_size; int /*<<< orphan*/  origin_sectors; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_t ; 

__attribute__((used)) static void set_discard_limits(struct cache *cache, struct queue_limits *limits)
{
	/*
	 * FIXME: these limits may be incompatible with the cache device
	 */
	limits->max_discard_sectors = min_t(sector_t, cache->discard_block_size * 1024,
					    cache->origin_sectors);
	limits->discard_granularity = cache->discard_block_size << SECTOR_SHIFT;
}