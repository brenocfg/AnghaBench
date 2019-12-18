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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {struct cache_set* c; } ;
struct cached_dev {int writeback_percent; int /*<<< orphan*/  bdev; TYPE_1__ disk; } ;
struct TYPE_4__ {int bucket_size; } ;
struct cache_set {int nbuckets; int /*<<< orphan*/  cached_dev_sectors; int /*<<< orphan*/  flash_dev_dirty_sectors; TYPE_2__ sb; } ;

/* Variables and functions */
 int WRITEBACK_SHARE_SHIFT ; 
 int atomic_long_read (int /*<<< orphan*/ *) ; 
 int bdev_sectors (int /*<<< orphan*/ ) ; 
 int div64_u64 (int,int /*<<< orphan*/ ) ; 
 int div_u64 (int,int) ; 

__attribute__((used)) static uint64_t __calc_target_rate(struct cached_dev *dc)
{
	struct cache_set *c = dc->disk.c;

	/*
	 * This is the size of the cache, minus the amount used for
	 * flash-only devices
	 */
	uint64_t cache_sectors = c->nbuckets * c->sb.bucket_size -
				atomic_long_read(&c->flash_dev_dirty_sectors);

	/*
	 * Unfortunately there is no control of global dirty data.  If the
	 * user states that they want 10% dirty data in the cache, and has,
	 * e.g., 5 backing volumes of equal size, we try and ensure each
	 * backing volume uses about 2% of the cache for dirty data.
	 */
	uint32_t bdev_share =
		div64_u64(bdev_sectors(dc->bdev) << WRITEBACK_SHARE_SHIFT,
				c->cached_dev_sectors);

	uint64_t cache_dirty_target =
		div_u64(cache_sectors * dc->writeback_percent, 100);

	/* Ensure each backing dev gets at least one dirty share */
	if (bdev_share < 1)
		bdev_share = 1;

	return (cache_dirty_target * bdev_share) >> WRITEBACK_SHARE_SHIFT;
}