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
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct bd_info_t {int /*<<< orphan*/  opened; } ;
struct exfat_sb_info {long debug_flags; struct bd_info_t bd_info; } ;

/* Variables and functions */
 long EXFAT_DEBUGFLAGS_ERROR_RW ; 
 struct exfat_sb_info* EXFAT_SB (struct super_block*) ; 
 int FFS_MEDIAERR ; 
 int sync_blockdev (int /*<<< orphan*/ ) ; 

int bdev_sync(struct super_block *sb)
{
	struct bd_info_t *p_bd = &(EXFAT_SB(sb)->bd_info);
#ifdef CONFIG_EXFAT_KERNEL_DEBUG
	struct exfat_sb_info *sbi = EXFAT_SB(sb);
	long flags = sbi->debug_flags;

	if (flags & EXFAT_DEBUGFLAGS_ERROR_RW)
		return FFS_MEDIAERR;
#endif /* CONFIG_EXFAT_KERNEL_DEBUG */

	if (!p_bd->opened)
		return FFS_MEDIAERR;

	return sync_blockdev(sb->s_bdev);
}