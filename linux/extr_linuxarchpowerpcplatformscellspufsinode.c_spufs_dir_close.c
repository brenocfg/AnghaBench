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
struct spu_context {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {struct dentry* d_parent; } ;
struct TYPE_4__ {struct spu_context* i_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 TYPE_2__* SPUFS_I (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct inode* d_inode (struct dentry*) ; 
 int dcache_dir_close (struct inode*,struct file*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int spufs_rmdir (struct inode*,struct dentry*) ; 

__attribute__((used)) static int spufs_dir_close(struct inode *inode, struct file *file)
{
	struct spu_context *ctx;
	struct inode *parent;
	struct dentry *dir;
	int ret;

	dir = file->f_path.dentry;
	parent = d_inode(dir->d_parent);
	ctx = SPUFS_I(d_inode(dir))->i_ctx;

	inode_lock_nested(parent, I_MUTEX_PARENT);
	ret = spufs_rmdir(parent, dir);
	inode_unlock(parent);
	WARN_ON(ret);

	return dcache_dir_close(inode, file);
}