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
struct cache {int sectors_per_block_shift; int /*<<< orphan*/  sectors_per_block; } ;
struct TYPE_2__ {int bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_size_is_power_of_two (struct cache*) ; 
 int /*<<< orphan*/  sector_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_oblock (int) ; 

__attribute__((used)) static dm_oblock_t get_bio_block(struct cache *cache, struct bio *bio)
{
	sector_t block_nr = bio->bi_iter.bi_sector;

	if (!block_size_is_power_of_two(cache))
		(void) sector_div(block_nr, cache->sectors_per_block);
	else
		block_nr >>= cache->sectors_per_block_shift;

	return to_oblock(block_nr);
}