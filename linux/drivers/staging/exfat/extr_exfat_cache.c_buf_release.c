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
struct fs_info_t {int /*<<< orphan*/  buf_cache_lru_list; } ;
struct buf_cache_t {int drv; int /*<<< orphan*/ * buf_bh; scalar_t__ flag; int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int /*<<< orphan*/  __brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b_sem ; 
 struct buf_cache_t* buf_cache_find (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (struct buf_cache_t*) ; 
 int /*<<< orphan*/  move_to_lru (struct buf_cache_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void buf_release(struct super_block *sb, sector_t sec)
{
	struct buf_cache_t *bp;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	down(&b_sem);

	bp = buf_cache_find(sb, sec);
	if (likely(bp)) {
		bp->drv = -1;
		bp->sec = ~0;
		bp->flag = 0;

		if (bp->buf_bh) {
			__brelse(bp->buf_bh);
			bp->buf_bh = NULL;
		}

		move_to_lru(bp, &p_fs->buf_cache_lru_list);
	}

	up(&b_sem);
}