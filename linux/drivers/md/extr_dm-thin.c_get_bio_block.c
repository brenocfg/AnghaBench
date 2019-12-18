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
struct thin_c {struct pool* pool; } ;
struct pool {int sectors_per_block_shift; int /*<<< orphan*/  sectors_per_block; } ;
struct TYPE_2__ {int bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int sector_t ;
typedef  int dm_block_t ;

/* Variables and functions */
 scalar_t__ block_size_is_power_of_two (struct pool*) ; 
 int /*<<< orphan*/  sector_div (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dm_block_t get_bio_block(struct thin_c *tc, struct bio *bio)
{
	struct pool *pool = tc->pool;
	sector_t block_nr = bio->bi_iter.bi_sector;

	if (block_size_is_power_of_two(pool))
		block_nr >>= pool->sectors_per_block_shift;
	else
		(void) sector_div(block_nr, pool->sectors_per_block);

	return block_nr;
}