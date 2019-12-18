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
typedef  int uint64_t ;
struct queue_limits {int io_opt; } ;
struct dm_target {struct cache* private; } ;
struct cache {int sectors_per_block; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  blk_limits_io_min (struct queue_limits*,int) ; 
 int /*<<< orphan*/  blk_limits_io_opt (struct queue_limits*,int) ; 
 int /*<<< orphan*/  disable_passdown_if_not_supported (struct cache*) ; 
 scalar_t__ do_div (int,int) ; 
 int /*<<< orphan*/  set_discard_limits (struct cache*,struct queue_limits*) ; 

__attribute__((used)) static void cache_io_hints(struct dm_target *ti, struct queue_limits *limits)
{
	struct cache *cache = ti->private;
	uint64_t io_opt_sectors = limits->io_opt >> SECTOR_SHIFT;

	/*
	 * If the system-determined stacked limits are compatible with the
	 * cache's blocksize (io_opt is a factor) do not override them.
	 */
	if (io_opt_sectors < cache->sectors_per_block ||
	    do_div(io_opt_sectors, cache->sectors_per_block)) {
		blk_limits_io_min(limits, cache->sectors_per_block << SECTOR_SHIFT);
		blk_limits_io_opt(limits, cache->sectors_per_block << SECTOR_SHIFT);
	}

	disable_passdown_if_not_supported(cache);
	set_discard_limits(cache, limits);
}