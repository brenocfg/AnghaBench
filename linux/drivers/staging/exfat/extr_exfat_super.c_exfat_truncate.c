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
struct inode {int i_blocks; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; struct super_block* i_sb; } ;
struct fs_info_t {int cluster_size; } ;
struct exfat_sb_info {struct fs_info_t fs_info; } ;
typedef  int loff_t ;
struct TYPE_3__ {scalar_t__ start_clu; } ;
struct TYPE_4__ {int mmu_private; TYPE_1__ fid; } ;

/* Variables and functions */
 TYPE_2__* EXFAT_I (struct inode*) ; 
 struct exfat_sb_info* EXFAT_SB (struct super_block*) ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 int /*<<< orphan*/  __lock_super (struct super_block*) ; 
 int /*<<< orphan*/  __unlock_super (struct super_block*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  exfat_sync_inode (struct inode*) ; 
 int ffsTruncateFile (struct inode*,int,int) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

__attribute__((used)) static void exfat_truncate(struct inode *inode, loff_t old_size)
{
	struct super_block *sb = inode->i_sb;
	struct exfat_sb_info *sbi = EXFAT_SB(sb);
	struct fs_info_t *p_fs = &(sbi->fs_info);
	int err;

	__lock_super(sb);

	/*
	 * This protects against truncating a file bigger than it was then
	 * trying to write into the hole.
	 */
	if (EXFAT_I(inode)->mmu_private > i_size_read(inode))
		EXFAT_I(inode)->mmu_private = i_size_read(inode);

	if (EXFAT_I(inode)->fid.start_clu == 0)
		goto out;

	err = ffsTruncateFile(inode, old_size, i_size_read(inode));
	if (err)
		goto out;

	inode->i_ctime = inode->i_mtime = current_time(inode);
	if (IS_DIRSYNC(inode))
		(void)exfat_sync_inode(inode);
	else
		mark_inode_dirty(inode);

	inode->i_blocks = ((i_size_read(inode) + (p_fs->cluster_size - 1)) &
			   ~((loff_t)p_fs->cluster_size - 1)) >> 9;
out:
	__unlock_super(sb);
}