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
struct inode {int i_mode; TYPE_1__* i_sb; } ;
struct hypfs_sb_info {int /*<<< orphan*/  lock; } ;
struct file {int f_mode; int /*<<< orphan*/  private_data; } ;
struct TYPE_4__ {char* i_private; } ;
struct TYPE_3__ {struct hypfs_sb_info* s_fs_info; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOMEM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IRUGO ; 
 int S_IWUGO ; 
 TYPE_2__* file_inode (struct file*) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 

__attribute__((used)) static int hypfs_open(struct inode *inode, struct file *filp)
{
	char *data = file_inode(filp)->i_private;
	struct hypfs_sb_info *fs_info;

	if (filp->f_mode & FMODE_WRITE) {
		if (!(inode->i_mode & S_IWUGO))
			return -EACCES;
	}
	if (filp->f_mode & FMODE_READ) {
		if (!(inode->i_mode & S_IRUGO))
			return -EACCES;
	}

	fs_info = inode->i_sb->s_fs_info;
	if(data) {
		mutex_lock(&fs_info->lock);
		filp->private_data = kstrdup(data, GFP_KERNEL);
		if (!filp->private_data) {
			mutex_unlock(&fs_info->lock);
			return -ENOMEM;
		}
		mutex_unlock(&fs_info->lock);
	}
	return nonseekable_open(inode, filp);
}