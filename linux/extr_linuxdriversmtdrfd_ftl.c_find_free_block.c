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
struct partition {int current_block; int total_blocks; int reserved_block; TYPE_1__* blocks; } ;
struct TYPE_2__ {scalar_t__ state; scalar_t__ free_sectors; } ;

/* Variables and functions */
 scalar_t__ BLOCK_UNUSED ; 
 int /*<<< orphan*/  erase_block (struct partition*,int) ; 
 int jiffies ; 

__attribute__((used)) static int find_free_block(struct partition *part)
{
	int block, stop;

	block = part->current_block == -1 ?
			jiffies % part->total_blocks : part->current_block;
	stop = block;

	do {
		if (part->blocks[block].free_sectors &&
				block != part->reserved_block)
			return block;

		if (part->blocks[block].state == BLOCK_UNUSED)
			erase_block(part, block);

		if (++block >= part->total_blocks)
			block = 0;

	} while (block != stop);

	return -1;
}