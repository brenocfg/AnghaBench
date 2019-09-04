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
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memtrace_debugfs_dir ; 
 int /*<<< orphan*/  memtrace_init_fops ; 
 int /*<<< orphan*/  powerpc_debugfs_root ; 

__attribute__((used)) static int memtrace_init(void)
{
	memtrace_debugfs_dir = debugfs_create_dir("memtrace",
						  powerpc_debugfs_root);
	if (!memtrace_debugfs_dir)
		return -1;

	debugfs_create_file("enable", 0600, memtrace_debugfs_dir,
			    NULL, &memtrace_init_fops);

	return 0;
}