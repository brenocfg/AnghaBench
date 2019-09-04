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
struct queue_limits {int io_opt; int max_sectors; scalar_t__ discard_granularity; } ;
struct TYPE_2__ {int /*<<< orphan*/  discard_enabled; } ;
struct pool_c {TYPE_1__ adjusted_pf; struct pool* pool; } ;
struct pool {int sectors_per_block; } ;
struct dm_target {struct pool_c* private; } ;
typedef  int sector_t ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  blk_limits_io_min (struct queue_limits*,int) ; 
 int /*<<< orphan*/  blk_limits_io_opt (struct queue_limits*,int) ; 
 int /*<<< orphan*/  disable_passdown_if_not_supported (struct pool_c*) ; 
 scalar_t__ is_factor (int,int) ; 
 int rounddown_pow_of_two (int) ; 

__attribute__((used)) static void pool_io_hints(struct dm_target *ti, struct queue_limits *limits)
{
	struct pool_c *pt = ti->private;
	struct pool *pool = pt->pool;
	sector_t io_opt_sectors = limits->io_opt >> SECTOR_SHIFT;

	/*
	 * If max_sectors is smaller than pool->sectors_per_block adjust it
	 * to the highest possible power-of-2 factor of pool->sectors_per_block.
	 * This is especially beneficial when the pool's data device is a RAID
	 * device that has a full stripe width that matches pool->sectors_per_block
	 * -- because even though partial RAID stripe-sized IOs will be issued to a
	 *    single RAID stripe; when aggregated they will end on a full RAID stripe
	 *    boundary.. which avoids additional partial RAID stripe writes cascading
	 */
	if (limits->max_sectors < pool->sectors_per_block) {
		while (!is_factor(pool->sectors_per_block, limits->max_sectors)) {
			if ((limits->max_sectors & (limits->max_sectors - 1)) == 0)
				limits->max_sectors--;
			limits->max_sectors = rounddown_pow_of_two(limits->max_sectors);
		}
	}

	/*
	 * If the system-determined stacked limits are compatible with the
	 * pool's blocksize (io_opt is a factor) do not override them.
	 */
	if (io_opt_sectors < pool->sectors_per_block ||
	    !is_factor(io_opt_sectors, pool->sectors_per_block)) {
		if (is_factor(pool->sectors_per_block, limits->max_sectors))
			blk_limits_io_min(limits, limits->max_sectors << SECTOR_SHIFT);
		else
			blk_limits_io_min(limits, pool->sectors_per_block << SECTOR_SHIFT);
		blk_limits_io_opt(limits, pool->sectors_per_block << SECTOR_SHIFT);
	}

	/*
	 * pt->adjusted_pf is a staging area for the actual features to use.
	 * They get transferred to the live pool in bind_control_target()
	 * called from pool_preresume().
	 */
	if (!pt->adjusted_pf.discard_enabled) {
		/*
		 * Must explicitly disallow stacking discard limits otherwise the
		 * block layer will stack them if pool's data device has support.
		 * QUEUE_FLAG_DISCARD wouldn't be set but there is no way for the
		 * user to see that, so make sure to set all discard limits to 0.
		 */
		limits->discard_granularity = 0;
		return;
	}

	disable_passdown_if_not_supported(pt);

	/*
	 * The pool uses the same discard limits as the underlying data
	 * device.  DM core has already set this up.
	 */
}