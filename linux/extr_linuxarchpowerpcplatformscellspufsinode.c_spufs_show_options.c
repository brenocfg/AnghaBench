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
struct spufs_sb_info {scalar_t__ debug; } ;
struct seq_file {int dummy; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct dentry {struct inode* d_inode; int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int S_IALLUGO ; 
 int from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 struct spufs_sb_info* spufs_get_sb_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spufs_show_options(struct seq_file *m, struct dentry *root)
{
	struct spufs_sb_info *sbi = spufs_get_sb_info(root->d_sb);
	struct inode *inode = root->d_inode;

	if (!uid_eq(inode->i_uid, GLOBAL_ROOT_UID))
		seq_printf(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, inode->i_uid));
	if (!gid_eq(inode->i_gid, GLOBAL_ROOT_GID))
		seq_printf(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, inode->i_gid));
	if ((inode->i_mode & S_IALLUGO) != 0775)
		seq_printf(m, ",mode=%o", inode->i_mode);
	if (sbi->debug)
		seq_puts(m, ",debug");
	return 0;
}