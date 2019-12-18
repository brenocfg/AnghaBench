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
struct inode {struct super_block* i_sb; } ;
struct fs_info_t {struct fs_func* fs_func; } ;
struct fs_func {scalar_t__ (* count_ext_entries ) (struct super_block*,struct chain_t*,scalar_t__,struct dentry_t*) ;int /*<<< orphan*/  (* delete_dir_entry ) (struct super_block*,struct chain_t*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct dentry_t {int dummy; } ;
struct chain_t {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 TYPE_1__* EXFAT_SB (struct super_block*) ; 
 int /*<<< orphan*/  buf_lock (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_unlock (struct super_block*,int /*<<< orphan*/ ) ; 
 struct dentry_t* get_entry_in_dir (struct super_block*,struct chain_t*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct super_block*,struct chain_t*,scalar_t__,struct dentry_t*) ; 
 int /*<<< orphan*/  stub2 (struct super_block*,struct chain_t*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void remove_file(struct inode *inode, struct chain_t *p_dir, s32 entry)
{
	s32 num_entries;
	sector_t sector;
	struct dentry_t *ep;
	struct super_block *sb = inode->i_sb;
	struct fs_info_t *p_fs = &(EXFAT_SB(sb)->fs_info);
	struct fs_func *fs_func = p_fs->fs_func;

	ep = get_entry_in_dir(sb, p_dir, entry, &sector);
	if (!ep)
		return;

	buf_lock(sb, sector);

	/* buf_lock() before call count_ext_entries() */
	num_entries = fs_func->count_ext_entries(sb, p_dir, entry, ep);
	if (num_entries < 0) {
		buf_unlock(sb, sector);
		return;
	}
	num_entries++;

	buf_unlock(sb, sector);

	/* (1) update the directory entry */
	fs_func->delete_dir_entry(sb, p_dir, entry, 0, num_entries);
}