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
struct cache {int discard_block_size; int sectors_per_block_shift; int /*<<< orphan*/  sectors_per_block; } ;
typedef  int dm_block_t ;

/* Variables and functions */
 int block_div (int,int /*<<< orphan*/ ) ; 
 scalar_t__ block_size_is_power_of_two (struct cache*) ; 

__attribute__((used)) static dm_block_t oblocks_per_dblock(struct cache *cache)
{
	dm_block_t oblocks = cache->discard_block_size;

	if (block_size_is_power_of_two(cache))
		oblocks >>= cache->sectors_per_block_shift;
	else
		oblocks = block_div(oblocks, cache->sectors_per_block);

	return oblocks;
}