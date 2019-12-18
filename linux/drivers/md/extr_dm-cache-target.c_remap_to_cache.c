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
struct cache {int sectors_per_block; int sectors_per_block_shift; TYPE_2__* cache_dev; } ;
struct TYPE_3__ {int bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_size_is_power_of_two (struct cache*) ; 
 int from_cblock (int /*<<< orphan*/ ) ; 
 int sector_div (int,int) ; 

__attribute__((used)) static void remap_to_cache(struct cache *cache, struct bio *bio,
			   dm_cblock_t cblock)
{
	sector_t bi_sector = bio->bi_iter.bi_sector;
	sector_t block = from_cblock(cblock);

	bio_set_dev(bio, cache->cache_dev->bdev);
	if (!block_size_is_power_of_two(cache))
		bio->bi_iter.bi_sector =
			(block * cache->sectors_per_block) +
			sector_div(bi_sector, cache->sectors_per_block);
	else
		bio->bi_iter.bi_sector =
			(block << cache->sectors_per_block_shift) |
			(bi_sector & (cache->sectors_per_block - 1));
}