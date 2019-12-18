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
typedef  int /*<<< orphan*/  u8 ;
struct super_block {int dummy; } ;
struct fs_info_t {int drv; int /*<<< orphan*/  FAT_cache_lru_list; } ;
struct buf_cache_t {int drv; TYPE_1__* buf_bh; scalar_t__ flag; int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {struct fs_info_t fs_info; } ;
struct TYPE_3__ {int /*<<< orphan*/ * b_data; } ;

/* Variables and functions */
 TYPE_2__* EXFAT_SB (struct super_block*) ; 
 struct buf_cache_t* FAT_cache_find (struct super_block*,int /*<<< orphan*/ ) ; 
 struct buf_cache_t* FAT_cache_get (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAT_cache_insert_hash (struct super_block*,struct buf_cache_t*) ; 
 int /*<<< orphan*/  FAT_cache_remove_hash (struct buf_cache_t*) ; 
 scalar_t__ FFS_SUCCESS ; 
 int /*<<< orphan*/  move_to_lru (struct buf_cache_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_to_mru (struct buf_cache_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ sector_read (struct super_block*,int /*<<< orphan*/ ,TYPE_1__**,int) ; 

u8 *FAT_getblk(struct super_block *sb, sector_t sec)
{
	struct buf_cache_t *bp;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	bp = FAT_cache_find(sb, sec);
	if (bp) {
		move_to_mru(bp, &p_fs->FAT_cache_lru_list);
		return bp->buf_bh->b_data;
	}

	bp = FAT_cache_get(sb, sec);

	FAT_cache_remove_hash(bp);

	bp->drv = p_fs->drv;
	bp->sec = sec;
	bp->flag = 0;

	FAT_cache_insert_hash(sb, bp);

	if (sector_read(sb, sec, &bp->buf_bh, 1) != FFS_SUCCESS) {
		FAT_cache_remove_hash(bp);
		bp->drv = -1;
		bp->sec = ~0;
		bp->flag = 0;
		bp->buf_bh = NULL;

		move_to_lru(bp, &p_fs->FAT_cache_lru_list);
		return NULL;
	}

	return bp->buf_bh->b_data;
}