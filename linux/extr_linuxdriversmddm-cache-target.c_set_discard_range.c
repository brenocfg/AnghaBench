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
struct discard_load_info {int discard_begin; int discard_end; int block_size; TYPE_1__* cache; } ;
typedef  int sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  discard_nr_blocks; int /*<<< orphan*/  discard_block_size; } ;

/* Variables and functions */
 int dm_sector_div_up (int,int /*<<< orphan*/ ) ; 
 int from_dblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_discard (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_dblock (int) ; 

__attribute__((used)) static void set_discard_range(struct discard_load_info *li)
{
	sector_t b, e;

	if (li->discard_begin == li->discard_end)
		return;

	/*
	 * Convert to sectors.
	 */
	b = li->discard_begin * li->block_size;
	e = li->discard_end * li->block_size;

	/*
	 * Then convert back to the current dblock size.
	 */
	b = dm_sector_div_up(b, li->cache->discard_block_size);
	sector_div(e, li->cache->discard_block_size);

	/*
	 * The origin may have shrunk, so we need to check we're still in
	 * bounds.
	 */
	if (e > from_dblock(li->cache->discard_nr_blocks))
		e = from_dblock(li->cache->discard_nr_blocks);

	for (; b < e; b++)
		set_discard(li->cache, to_dblock(b));
}