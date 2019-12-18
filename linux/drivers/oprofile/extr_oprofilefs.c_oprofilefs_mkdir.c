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
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char const*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 struct inode* oprofilefs_get_inode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 

struct dentry *oprofilefs_mkdir(struct dentry *parent, char const *name)
{
	struct dentry *dentry;
	struct inode *inode;

	inode_lock(d_inode(parent));
	dentry = d_alloc_name(parent, name);
	if (!dentry) {
		inode_unlock(d_inode(parent));
		return NULL;
	}
	inode = oprofilefs_get_inode(parent->d_sb, S_IFDIR | 0755);
	if (!inode) {
		dput(dentry);
		inode_unlock(d_inode(parent));
		return NULL;
	}
	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	d_add(dentry, inode);
	inode_unlock(d_inode(parent));
	return dentry;
}