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
struct bitmap_counts {unsigned long chunkshift; TYPE_1__* bp; } ;
typedef  unsigned long sector_t ;
struct TYPE_2__ {int count; } ;

/* Variables and functions */
 unsigned long PAGE_COUNTER_SHIFT ; 
 int /*<<< orphan*/  md_bitmap_checkfree (struct bitmap_counts*,unsigned long) ; 

__attribute__((used)) static void md_bitmap_count_page(struct bitmap_counts *bitmap,
				 sector_t offset, int inc)
{
	sector_t chunk = offset >> bitmap->chunkshift;
	unsigned long page = chunk >> PAGE_COUNTER_SHIFT;
	bitmap->bp[page].count += inc;
	md_bitmap_checkfree(bitmap, page);
}