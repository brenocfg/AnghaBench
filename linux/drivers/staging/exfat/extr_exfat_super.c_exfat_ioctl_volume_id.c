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
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fs_info_t {int vol_id; } ;
struct exfat_sb_info {struct fs_info_t fs_info; } ;

/* Variables and functions */
 struct exfat_sb_info* EXFAT_SB (struct super_block*) ; 

__attribute__((used)) static int exfat_ioctl_volume_id(struct inode *dir)
{
	struct super_block *sb = dir->i_sb;
	struct exfat_sb_info *sbi = EXFAT_SB(sb);
	struct fs_info_t *p_fs = &(sbi->fs_info);

	return p_fs->vol_id;
}