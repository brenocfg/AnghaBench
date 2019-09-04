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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 scalar_t__ ERR_PTR (int /*<<< orphan*/ ) ; 
 int S_IFREG ; 
 scalar_t__ debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char*,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ debugfs_root ; 
 int /*<<< orphan*/  kfd_debugfs_fops ; 
 int /*<<< orphan*/  kfd_debugfs_hang_hws_fops ; 
 int /*<<< orphan*/ * kfd_debugfs_hqds_by_device ; 
 int /*<<< orphan*/ * kfd_debugfs_mqds_by_process ; 
 int /*<<< orphan*/ * kfd_debugfs_rls_by_device ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

void kfd_debugfs_init(void)
{
	struct dentry *ent;

	debugfs_root = debugfs_create_dir("kfd", NULL);
	if (!debugfs_root || debugfs_root == ERR_PTR(-ENODEV)) {
		pr_warn("Failed to create kfd debugfs dir\n");
		return;
	}

	ent = debugfs_create_file("mqds", S_IFREG | 0444, debugfs_root,
				  kfd_debugfs_mqds_by_process,
				  &kfd_debugfs_fops);
	if (!ent)
		pr_warn("Failed to create mqds in kfd debugfs\n");

	ent = debugfs_create_file("hqds", S_IFREG | 0444, debugfs_root,
				  kfd_debugfs_hqds_by_device,
				  &kfd_debugfs_fops);
	if (!ent)
		pr_warn("Failed to create hqds in kfd debugfs\n");

	ent = debugfs_create_file("rls", S_IFREG | 0444, debugfs_root,
				  kfd_debugfs_rls_by_device,
				  &kfd_debugfs_fops);

	ent = debugfs_create_file("hang_hws", S_IFREG | 0644, debugfs_root,
				  NULL,
				  &kfd_debugfs_hang_hws_fops);

	if (!ent)
		pr_warn("Failed to create rls in kfd debugfs\n");
}