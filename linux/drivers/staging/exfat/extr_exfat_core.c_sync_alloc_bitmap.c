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
struct fs_info_t {int map_sectors; int /*<<< orphan*/ * vol_amap; } ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int /*<<< orphan*/  sync_dirty_buffer (int /*<<< orphan*/ ) ; 

void sync_alloc_bitmap(struct super_block *sb)
{
	int i;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	if (!p_fs->vol_amap)
		return;

	for (i = 0; i < p_fs->map_sectors; i++)
		sync_dirty_buffer(p_fs->vol_amap[i]);
}