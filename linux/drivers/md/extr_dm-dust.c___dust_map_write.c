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
struct dust_device {int /*<<< orphan*/  sect_per_block; int /*<<< orphan*/  quiet_mode; int /*<<< orphan*/  badblock_count; int /*<<< orphan*/  badblocklist; } ;
struct badblock {int /*<<< orphan*/  node; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMINFO (char*,unsigned long long) ; 
 struct badblock* dust_rb_search (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct badblock*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sector_div (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dust_map_write(struct dust_device *dd, sector_t thisblock)
{
	struct badblock *bblk = dust_rb_search(&dd->badblocklist, thisblock);

	if (bblk) {
		rb_erase(&bblk->node, &dd->badblocklist);
		dd->badblock_count--;
		kfree(bblk);
		if (!dd->quiet_mode) {
			sector_div(thisblock, dd->sect_per_block);
			DMINFO("block %llu removed from badblocklist by write",
			       (unsigned long long)thisblock);
		}
	}
}