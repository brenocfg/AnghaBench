#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_3__ {int /*<<< orphan*/  mtd; } ;
struct partition {int block_size; int total_blocks; int reserved_block; int data_sectors_per_block; int current_block; TYPE_2__* blocks; TYPE_1__ mbd; } ;
struct TYPE_4__ {int used_sectors; scalar_t__ free_sectors; scalar_t__ erases; } ;

/* Variables and functions */
 int ENOSPC ; 
 int erase_block (struct partition*,int) ; 
 int move_block_contents (struct partition*,int,int*) ; 
 int /*<<< orphan*/  mtd_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,scalar_t__) ; 

__attribute__((used)) static int reclaim_block(struct partition *part, u_long *old_sector)
{
	int block, best_block, score, old_sector_block;
	int rc;

	/* we have a race if sync doesn't exist */
	mtd_sync(part->mbd.mtd);

	score = 0x7fffffff; /* MAX_INT */
	best_block = -1;
	if (*old_sector != -1)
		old_sector_block = *old_sector / part->block_size;
	else
		old_sector_block = -1;

	for (block=0; block<part->total_blocks; block++) {
		int this_score;

		if (block == part->reserved_block)
			continue;

		/*
		 * Postpone reclaiming if there is a free sector as
		 * more removed sectors is more efficient (have to move
		 * less).
		 */
		if (part->blocks[block].free_sectors)
			return 0;

		this_score = part->blocks[block].used_sectors;

		if (block == old_sector_block)
			this_score--;
		else {
			/* no point in moving a full block */
			if (part->blocks[block].used_sectors ==
					part->data_sectors_per_block)
				continue;
		}

		this_score += part->blocks[block].erases;

		if (this_score < score) {
			best_block = block;
			score = this_score;
		}
	}

	if (best_block == -1)
		return -ENOSPC;

	part->current_block = -1;
	part->reserved_block = best_block;

	pr_debug("reclaim_block: reclaiming block #%d with %d used "
		 "%d free sectors\n", best_block,
		 part->blocks[best_block].used_sectors,
		 part->blocks[best_block].free_sectors);

	if (part->blocks[best_block].used_sectors)
		rc = move_block_contents(part, best_block, old_sector);
	else
		rc = erase_block(part, best_block);

	return rc;
}