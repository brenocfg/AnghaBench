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
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ MAX_DISCARD_BLOCKS ; 
 int /*<<< orphan*/  sector_div (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool too_many_discard_blocks(sector_t discard_block_size,
				    sector_t origin_size)
{
	(void) sector_div(origin_size, discard_block_size);

	return origin_size > MAX_DISCARD_BLOCKS;
}