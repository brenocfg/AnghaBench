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
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int qibfs_mknod (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ,struct file_operations const*,void*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int create_file(const char *name, umode_t mode,
		       struct dentry *parent, struct dentry **dentry,
		       const struct file_operations *fops, void *data)
{
	int error;

	inode_lock(d_inode(parent));
	*dentry = lookup_one_len(name, parent, strlen(name));
	if (!IS_ERR(*dentry))
		error = qibfs_mknod(d_inode(parent), *dentry,
				    mode, fops, data);
	else
		error = PTR_ERR(*dentry);
	inode_unlock(d_inode(parent));

	return error;
}