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
typedef  int sector_t ;

/* Variables and functions */
 scalar_t__ too_many_discard_blocks (int,int) ; 

__attribute__((used)) static sector_t calculate_discard_block_size(sector_t cache_block_size,
					     sector_t origin_size)
{
	sector_t discard_block_size = cache_block_size;

	if (origin_size)
		while (too_many_discard_blocks(discard_block_size, origin_size))
			discard_block_size *= 2;

	return discard_block_size;
}