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
struct bitmap_page {int pending; } ;
struct bitmap_counts {unsigned long chunkshift; struct bitmap_page* bp; } ;
typedef  unsigned long sector_t ;

/* Variables and functions */
 unsigned long PAGE_COUNTER_SHIFT ; 

__attribute__((used)) static void md_bitmap_set_pending(struct bitmap_counts *bitmap, sector_t offset)
{
	sector_t chunk = offset >> bitmap->chunkshift;
	unsigned long page = chunk >> PAGE_COUNTER_SHIFT;
	struct bitmap_page *bp = &bitmap->bp[page];

	if (!bp->pending)
		bp->pending = 1;
}