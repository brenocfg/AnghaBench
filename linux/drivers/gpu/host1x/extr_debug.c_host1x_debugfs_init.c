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
struct host1x {struct dentry* debugfs; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct host1x*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host1x_debug_all_fops ; 
 int /*<<< orphan*/  host1x_debug_fops ; 
 int /*<<< orphan*/  host1x_debug_force_timeout_channel ; 
 int /*<<< orphan*/  host1x_debug_force_timeout_pid ; 
 int /*<<< orphan*/  host1x_debug_force_timeout_val ; 
 int /*<<< orphan*/  host1x_debug_trace_cmdbuf ; 
 int /*<<< orphan*/  host1x_hw_debug_init (struct host1x*,struct dentry*) ; 

__attribute__((used)) static void host1x_debugfs_init(struct host1x *host1x)
{
	struct dentry *de = debugfs_create_dir("tegra-host1x", NULL);

	/* Store the created entry */
	host1x->debugfs = de;

	debugfs_create_file("status", S_IRUGO, de, host1x, &host1x_debug_fops);
	debugfs_create_file("status_all", S_IRUGO, de, host1x,
			    &host1x_debug_all_fops);

	debugfs_create_u32("trace_cmdbuf", S_IRUGO|S_IWUSR, de,
			   &host1x_debug_trace_cmdbuf);

	host1x_hw_debug_init(host1x, de);

	debugfs_create_u32("force_timeout_pid", S_IRUGO|S_IWUSR, de,
			   &host1x_debug_force_timeout_pid);
	debugfs_create_u32("force_timeout_val", S_IRUGO|S_IWUSR, de,
			   &host1x_debug_force_timeout_val);
	debugfs_create_u32("force_timeout_channel", S_IRUGO|S_IWUSR, de,
			   &host1x_debug_force_timeout_channel);
}