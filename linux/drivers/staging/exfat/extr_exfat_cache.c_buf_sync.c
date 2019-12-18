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
struct buf_cache_t {scalar_t__ drv; int flag; struct buf_cache_t* next; int /*<<< orphan*/  buf_bh; } ;
struct fs_info_t {scalar_t__ drv; struct buf_cache_t buf_cache_lru_list; } ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 int DIRTYBIT ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int /*<<< orphan*/  b_sem ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_dirty_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void buf_sync(struct super_block *sb)
{
	struct buf_cache_t *bp;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);

	down(&b_sem);

	bp = p_fs->buf_cache_lru_list.next;
	while (bp != &p_fs->buf_cache_lru_list) {
		if ((bp->drv == p_fs->drv) && (bp->flag & DIRTYBIT)) {
			sync_dirty_buffer(bp->buf_bh);
			bp->flag &= ~(DIRTYBIT);
		}
		bp = bp->next;
	}

	up(&b_sem);
}