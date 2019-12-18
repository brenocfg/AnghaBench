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

/* Variables and functions */
 int S_IFREG ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_root ; 
 int /*<<< orphan*/  kfd_debugfs_fops ; 
 int /*<<< orphan*/  kfd_debugfs_hang_hws_fops ; 
 int /*<<< orphan*/ * kfd_debugfs_hqds_by_device ; 
 int /*<<< orphan*/ * kfd_debugfs_mqds_by_process ; 
 int /*<<< orphan*/ * kfd_debugfs_rls_by_device ; 

void kfd_debugfs_init(void)
{
	debugfs_root = debugfs_create_dir("kfd", NULL);

	debugfs_create_file("mqds", S_IFREG | 0444, debugfs_root,
			    kfd_debugfs_mqds_by_process, &kfd_debugfs_fops);
	debugfs_create_file("hqds", S_IFREG | 0444, debugfs_root,
			    kfd_debugfs_hqds_by_device, &kfd_debugfs_fops);
	debugfs_create_file("rls", S_IFREG | 0444, debugfs_root,
			    kfd_debugfs_rls_by_device, &kfd_debugfs_fops);
	debugfs_create_file("hang_hws", S_IFREG | 0644, debugfs_root,
			    NULL, &kfd_debugfs_hang_hws_fops);
}