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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSEUDO_FS_MAGIC ; 
 int /*<<< orphan*/  cxl_fs_dops ; 
 struct dentry* mount_pseudo (struct file_system_type*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *cxl_fs_mount(struct file_system_type *fs_type, int flags,
				const char *dev_name, void *data)
{
	return mount_pseudo(fs_type, "cxl:", NULL, &cxl_fs_dops,
			CXL_PSEUDO_FS_MAGIC);
}