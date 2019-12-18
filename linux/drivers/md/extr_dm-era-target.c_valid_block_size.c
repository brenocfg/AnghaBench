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
typedef  int dm_block_t ;

/* Variables and functions */
 int MIN_BLOCK_SIZE ; 

__attribute__((used)) static bool valid_block_size(dm_block_t block_size)
{
	bool greater_than_zero = block_size > 0;
	bool multiple_of_min_block_size = (block_size & (MIN_BLOCK_SIZE - 1)) == 0;

	return greater_than_zero && multiple_of_min_block_size;
}