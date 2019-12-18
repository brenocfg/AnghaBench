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
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 long EXFAT_DEBUGFLAGS_ERROR_RW ; 
 struct exfat_sb_info* EXFAT_SB (struct super_block*) ; 
 int FFS_MEDIAERR ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct buffer_head* __bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 struct buffer_head* __getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int bdev_read(struct super_block *sb, sector_t secno, struct buffer_head **bh,
	      u32 num_secs, bool read)
{
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

	if (*bh)
		__brelse(*bh);

	if (read)
		*bh = __bread(sb->s_bdev, secno,
			      num_secs << p_bd->sector_size_bits);
	else
		*bh = __getblk(sb->s_bdev, secno,
			       num_secs << p_bd->sector_size_bits);

	if (*bh)
		return 0;

	WARN(!p_fs->dev_ejected,
	     "[EXFAT] No bh, device seems wrong or to be ejected.\n");

	return FFS_MEDIAERR;
}