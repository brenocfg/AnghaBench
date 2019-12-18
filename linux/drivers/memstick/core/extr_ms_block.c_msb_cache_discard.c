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
struct msb_data {scalar_t__ cache_block_lba; int /*<<< orphan*/  pages_in_block; int /*<<< orphan*/  valid_cache_bitmap; int /*<<< orphan*/  cache_flush_timer; } ;

/* Variables and functions */
 scalar_t__ MS_BLOCK_INVALID ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_verbose (char*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msb_cache_discard(struct msb_data *msb)
{
	if (msb->cache_block_lba == MS_BLOCK_INVALID)
		return;

	del_timer_sync(&msb->cache_flush_timer);

	dbg_verbose("Discarding the write cache");
	msb->cache_block_lba = MS_BLOCK_INVALID;
	bitmap_zero(&msb->valid_cache_bitmap, msb->pages_in_block);
}