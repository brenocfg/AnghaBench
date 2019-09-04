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
struct file_system_type {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 struct dentry* mount_single (struct file_system_type*,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_super ; 
 int /*<<< orphan*/  qibfs_fill_super ; 

__attribute__((used)) static struct dentry *qibfs_mount(struct file_system_type *fs_type, int flags,
			const char *dev_name, void *data)
{
	struct dentry *ret;

	ret = mount_single(fs_type, flags, data, qibfs_fill_super);
	if (!IS_ERR(ret))
		qib_super = ret->d_sb;
	return ret;
}