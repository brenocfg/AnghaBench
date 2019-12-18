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
struct discard_load_info {scalar_t__ discard_end; scalar_t__ discard_begin; int /*<<< orphan*/  block_size; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  dm_dblock_t ;

/* Variables and functions */
 scalar_t__ from_dblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_discard_range (struct discard_load_info*) ; 

__attribute__((used)) static int load_discard(void *context, sector_t discard_block_size,
			dm_dblock_t dblock, bool discard)
{
	struct discard_load_info *li = context;

	li->block_size = discard_block_size;

	if (discard) {
		if (from_dblock(dblock) == li->discard_end)
			/*
			 * We're already in a discard range, just extend it.
			 */
			li->discard_end = li->discard_end + 1ULL;

		else {
			/*
			 * Emit the old range and start a new one.
			 */
			set_discard_range(li);
			li->discard_begin = from_dblock(dblock);
			li->discard_end = li->discard_begin + 1ULL;
		}
	} else {
		set_discard_range(li);
		li->discard_begin = li->discard_end = 0;
	}

	return 0;
}