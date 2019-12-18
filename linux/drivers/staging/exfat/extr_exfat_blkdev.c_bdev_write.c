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
typedef  int u32 ;
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct fs_info_t {int /*<<< orphan*/  dev_ejected; } ;
struct bd_info_t {int sector_size_bits; int /*<<< orphan*/  opened; } ;
struct exfat_sb_info {long debug_flags; struct fs_info_t fs_info; struct bd_info_t bd_info; } ;
struct buffer_head {scalar_t__ b_blocknr; int /*<<< orphan*/  b_data; } ;
typedef  scalar_t__ sector_t ;
typedef  int s32 ;

/* Variables and functions */
 long EXFAT_DEBUGFLAGS_ERROR_RW ; 
 struct exfat_sb_info* EXFAT_SB (struct super_block*) ; 
 int FFS_MEDIAERR ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 struct buffer_head* __getblk (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ sync_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

int bdev_write(struct super_block *sb, sector_t secno, struct buffer_head *bh,
	       u32 num_secs, bool sync)
{
	s32 count;
	struct buffer_head *bh2;
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
#ifdef CONFIG_EXFAT_KERNEL_DEBUG
	struct exfat_sb_info *sbi = EXFAT_SB(sb);
	long flags = sbi->debug_flags;

	if (flags & EXFAT_DEBUGFLAGS_ERROR_RW)
		return FFS_MEDIAERR;
#endif /* CONFIG_EXFAT_KERNEL_DEBUG */

	if (!p_bd->opened)
		return FFS_MEDIAERR;

	if (secno == bh->b_blocknr) {
		lock_buffer(bh);
		set_buffer_uptodate(bh);
		mark_buffer_dirty(bh);
		unlock_buffer(bh);
		if (sync && (sync_dirty_buffer(bh) != 0))
			return FFS_MEDIAERR;
	} else {
		count = num_secs << p_bd->sector_size_bits;

		bh2 = __getblk(sb->s_bdev, secno, count);
		if (!bh2)
			goto no_bh;

		lock_buffer(bh2);
		memcpy(bh2->b_data, bh->b_data, count);
		set_buffer_uptodate(bh2);
		mark_buffer_dirty(bh2);
		unlock_buffer(bh2);
		if (sync && (sync_dirty_buffer(bh2) != 0)) {
			__brelse(bh2);
			goto no_bh;
		}
		__brelse(bh2);
	}

	return 0;

no_bh:
	WARN(!p_fs->dev_ejected,
	     "[EXFAT] No bh, device seems wrong or to be ejected.\n");

	return FFS_MEDIAERR;
}