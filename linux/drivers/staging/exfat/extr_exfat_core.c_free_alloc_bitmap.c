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
struct super_block {int dummy; } ;
struct fs_info_t {int map_sectors; int /*<<< orphan*/ * vol_amap; int /*<<< orphan*/  pbr_bh; } ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int /*<<< orphan*/  __brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void free_alloc_bitmap(struct super_block *sb)
{
	int i;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	brelse(p_fs->pbr_bh);

	for (i = 0; i < p_fs->map_sectors; i++)
		__brelse(p_fs->vol_amap[i]);

	kfree(p_fs->vol_amap);
	p_fs->vol_amap = NULL;
}