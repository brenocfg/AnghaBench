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
struct pool {unsigned long long sectors_per_block; int sectors_per_block_shift; } ;
struct TYPE_2__ {int bi_sector; int bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int sector_t ;
typedef  int dm_block_t ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 scalar_t__ block_size_is_power_of_two (struct pool*) ; 
 int /*<<< orphan*/  sector_div (int,unsigned long long) ; 

__attribute__((used)) static void get_bio_block_range(struct thin_c *tc, struct bio *bio,
				dm_block_t *begin, dm_block_t *end)
{
	struct pool *pool = tc->pool;
	sector_t b = bio->bi_iter.bi_sector;
	sector_t e = b + (bio->bi_iter.bi_size >> SECTOR_SHIFT);

	b += pool->sectors_per_block - 1ull; /* so we round up */

	if (block_size_is_power_of_two(pool)) {
		b >>= pool->sectors_per_block_shift;
		e >>= pool->sectors_per_block_shift;
	} else {
		(void) sector_div(b, pool->sectors_per_block);
		(void) sector_div(e, pool->sectors_per_block);
	}

	if (e < b)
		/* Can happen if the bio is within a single block. */
		e = b;

	*begin = b;
	*end = e;
}