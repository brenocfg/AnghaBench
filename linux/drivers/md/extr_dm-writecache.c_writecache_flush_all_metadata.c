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
struct dm_writecache {int /*<<< orphan*/  dirty_bitmap_size; int /*<<< orphan*/  dirty_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  WC_MODE_PMEM (struct dm_writecache*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writecache_flush_all_metadata(struct dm_writecache *wc)
{
	if (!WC_MODE_PMEM(wc))
		memset(wc->dirty_bitmap, -1, wc->dirty_bitmap_size);
}