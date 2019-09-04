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
typedef  unsigned int sector_t ;

/* Variables and functions */
 unsigned int max (unsigned int,unsigned int) ; 
 scalar_t__ too_many_hotspot_blocks (unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void calc_hotspot_params(sector_t origin_size,
				sector_t cache_block_size,
				unsigned nr_cache_blocks,
				sector_t *hotspot_block_size,
				unsigned *nr_hotspot_blocks)
{
	*hotspot_block_size = cache_block_size * 16u;
	*nr_hotspot_blocks = max(nr_cache_blocks / 4u, 1024u);

	while ((*hotspot_block_size > cache_block_size) &&
	       too_many_hotspot_blocks(origin_size, *hotspot_block_size, *nr_hotspot_blocks))
		*hotspot_block_size /= 2u;
}