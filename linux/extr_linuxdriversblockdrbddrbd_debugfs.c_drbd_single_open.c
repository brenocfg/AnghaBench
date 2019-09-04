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
struct kref {int dummy; } ;
struct TYPE_3__ {TYPE_2__* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {struct dentry* d_parent; } ;

/* Variables and functions */
 int ESTALE ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ kref_get_unless_zero (struct kref*) ; 
 int /*<<< orphan*/  kref_put (struct kref*,void (*) (struct kref*)) ; 
 scalar_t__ simple_positive (TYPE_2__*) ; 
 int single_open (struct file*,int (*) (struct seq_file*,void*),void*) ; 

__attribute__((used)) static int drbd_single_open(struct file *file, int (*show)(struct seq_file *, void *),
		                void *data, struct kref *kref,
				void (*release)(struct kref *))
{
	struct dentry *parent;
	int ret = -ESTALE;

	/* Are we still linked,
	 * or has debugfs_remove() already been called? */
	parent = file->f_path.dentry->d_parent;
	/* serialize with d_delete() */
	inode_lock(d_inode(parent));
	/* Make sure the object is still alive */
	if (simple_positive(file->f_path.dentry)
	&& kref_get_unless_zero(kref))
		ret = 0;
	inode_unlock(d_inode(parent));
	if (!ret) {
		ret = single_open(file, show, data);
		if (ret)
			kref_put(kref, release);
	}
	return ret;
}