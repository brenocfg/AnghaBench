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
struct fs_info_t {int sectors_per_clu_bits; scalar_t__ drv; struct buf_cache_t* FAT_cache_hash_list; } ;
struct buf_cache_t {scalar_t__ drv; int sec; int /*<<< orphan*/  buf_bh; struct buf_cache_t* hash_next; } ;
typedef  int sector_t ;
typedef  size_t s32 ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int FAT_CACHE_HASH_SIZE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  touch_buffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct buf_cache_t *FAT_cache_find(struct super_block *sb, sector_t sec)
{
	s32 off;
	struct buf_cache_t *bp, *hp;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	off = (sec +
	       (sec >> p_fs->sectors_per_clu_bits)) & (FAT_CACHE_HASH_SIZE - 1);

	hp = &p_fs->FAT_cache_hash_list[off];
	for (bp = hp->hash_next; bp != hp; bp = bp->hash_next) {
		if ((bp->drv == p_fs->drv) && (bp->sec == sec)) {
			WARN(!bp->buf_bh,
			     "[EXFAT] FAT_cache has no bh. It will make system panic.\n");

			touch_buffer(bp->buf_bh);
			return bp;
		}
	}
	return NULL;
}