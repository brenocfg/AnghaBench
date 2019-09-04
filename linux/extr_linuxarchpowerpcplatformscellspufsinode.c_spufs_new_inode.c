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
typedef  int /*<<< orphan*/  umode_t ;
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  get_next_ino () ; 
 struct inode* new_inode (struct super_block*) ; 

__attribute__((used)) static struct inode *
spufs_new_inode(struct super_block *sb, umode_t mode)
{
	struct inode *inode;

	inode = new_inode(sb);
	if (!inode)
		goto out;

	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();
	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
out:
	return inode;
}