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

__attribute__((used)) static bool too_many_hotspot_blocks(sector_t origin_size,
				    sector_t hotspot_block_size,
				    unsigned nr_hotspot_blocks)
{
	return (hotspot_block_size * nr_hotspot_blocks) > origin_size;
}