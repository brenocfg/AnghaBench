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
 int /*<<< orphan*/  kfd_chardev_exit () ; 
 int /*<<< orphan*/  kfd_debugfs_fini () ; 
 int /*<<< orphan*/  kfd_process_destroy_wq () ; 
 int /*<<< orphan*/  kfd_procfs_shutdown () ; 
 int /*<<< orphan*/  kfd_topology_shutdown () ; 

__attribute__((used)) static void kfd_exit(void)
{
	kfd_debugfs_fini();
	kfd_process_destroy_wq();
	kfd_procfs_shutdown();
	kfd_topology_shutdown();
	kfd_chardev_exit();
}