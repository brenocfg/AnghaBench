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
struct buf_cache_t {int drv; struct buf_cache_t* next; int /*<<< orphan*/ * buf_bh; scalar_t__ flag; int /*<<< orphan*/  sec; } ;
struct fs_info_t {int drv; struct buf_cache_t buf_cache_lru_list; } ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int /*<<< orphan*/  __brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b_sem ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void buf_release_all(struct super_block *sb)
{
	struct buf_cache_t *bp;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	down(&b_sem);

	bp = p_fs->buf_cache_lru_list.next;
	while (bp != &p_fs->buf_cache_lru_list) {
		if (bp->drv == p_fs->drv) {
			bp->drv = -1;
			bp->sec = ~0;
			bp->flag = 0;

			if (bp->buf_bh) {
				__brelse(bp->buf_bh);
				bp->buf_bh = NULL;
			}
		}
		bp = bp->next;
	}

	up(&b_sem);
}