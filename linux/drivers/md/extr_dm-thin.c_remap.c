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
struct thin_c {TYPE_2__* pool_dev; struct pool* pool; } ;
struct pool {int sectors_per_block_shift; int sectors_per_block; } ;
struct TYPE_3__ {int bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int sector_t ;
typedef  int dm_block_t ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ block_size_is_power_of_two (struct pool*) ; 
 int sector_div (int,int) ; 

__attribute__((used)) static void remap(struct thin_c *tc, struct bio *bio, dm_block_t block)
{
	struct pool *pool = tc->pool;
	sector_t bi_sector = bio->bi_iter.bi_sector;

	bio_set_dev(bio, tc->pool_dev->bdev);
	if (block_size_is_power_of_two(pool))
		bio->bi_iter.bi_sector =
			(block << pool->sectors_per_block_shift) |
			(bi_sector & (pool->sectors_per_block - 1));
	else
		bio->bi_iter.bi_sector = (block * pool->sectors_per_block) +
				 sector_div(bi_sector, pool->sectors_per_block);
}