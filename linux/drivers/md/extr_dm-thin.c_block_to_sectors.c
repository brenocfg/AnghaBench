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
struct pool {int sectors_per_block_shift; int sectors_per_block; } ;
typedef  int sector_t ;
typedef  int dm_block_t ;

/* Variables and functions */
 scalar_t__ block_size_is_power_of_two (struct pool*) ; 

__attribute__((used)) static sector_t block_to_sectors(struct pool *pool, dm_block_t b)
{
	return block_size_is_power_of_two(pool) ?
		(b << pool->sectors_per_block_shift) :
		(b * pool->sectors_per_block);
}