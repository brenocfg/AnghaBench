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
struct csi_state {int /*<<< orphan*/  debugfs_root; int /*<<< orphan*/  debug; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct dentry* debugfs_create_bool (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct csi_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_initialized () ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_csis_dump_regs_fops ; 

__attribute__((used)) static int mipi_csis_debugfs_init(struct csi_state *state)
{
	struct dentry *d;

	if (!debugfs_initialized())
		return -ENODEV;

	state->debugfs_root = debugfs_create_dir(dev_name(state->dev), NULL);
	if (!state->debugfs_root)
		return -ENOMEM;

	d = debugfs_create_bool("debug_enable", 0600, state->debugfs_root,
				&state->debug);
	if (!d)
		goto remove_debugfs;

	d = debugfs_create_file("dump_regs", 0600, state->debugfs_root,
				state, &mipi_csis_dump_regs_fops);
	if (!d)
		goto remove_debugfs;

	return 0;

remove_debugfs:
	debugfs_remove_recursive(state->debugfs_root);

	return -ENOMEM;
}