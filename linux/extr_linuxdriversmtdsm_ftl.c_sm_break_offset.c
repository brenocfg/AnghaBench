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
typedef  int u64 ;
struct sm_ftl {int zone_count; int /*<<< orphan*/  max_lba; int /*<<< orphan*/  block_size; } ;
typedef  int loff_t ;

/* Variables and functions */
 int do_div (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sm_break_offset(struct sm_ftl *ftl, loff_t loffset,
			    int *zone, int *block, int *boffset)
{
	u64 offset = loffset;
	*boffset = do_div(offset, ftl->block_size);
	*block = do_div(offset, ftl->max_lba);
	*zone = offset >= ftl->zone_count ? -1 : offset;
}