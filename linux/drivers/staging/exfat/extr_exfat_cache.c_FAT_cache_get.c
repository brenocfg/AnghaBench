#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_3__ {struct buf_cache_t* prev; } ;
struct fs_info_t {TYPE_1__ FAT_cache_lru_list; } ;
struct buf_cache_t {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 int /*<<< orphan*/  move_to_mru (struct buf_cache_t*,TYPE_1__*) ; 

__attribute__((used)) static struct buf_cache_t *FAT_cache_get(struct super_block *sb, sector_t sec)
{
	struct buf_cache_t *bp;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	bp = p_fs->FAT_cache_lru_list.prev;

	move_to_mru(bp, &p_fs->FAT_cache_lru_list);
	return bp;
}