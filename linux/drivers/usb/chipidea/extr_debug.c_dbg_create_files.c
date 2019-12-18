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
struct ci_hdrc {int /*<<< orphan*/  debugfs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  ci_device_fops ; 
 int /*<<< orphan*/  ci_otg_fops ; 
 scalar_t__ ci_otg_is_fsm_mode (struct ci_hdrc*) ; 
 int /*<<< orphan*/  ci_port_test_fops ; 
 int /*<<< orphan*/  ci_qheads_fops ; 
 int /*<<< orphan*/  ci_registers_fops ; 
 int /*<<< orphan*/  ci_requests_fops ; 
 int /*<<< orphan*/  ci_role_fops ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct ci_hdrc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 

void dbg_create_files(struct ci_hdrc *ci)
{
	ci->debugfs = debugfs_create_dir(dev_name(ci->dev), NULL);

	debugfs_create_file("device", S_IRUGO, ci->debugfs, ci,
			    &ci_device_fops);
	debugfs_create_file("port_test", S_IRUGO | S_IWUSR, ci->debugfs, ci,
			    &ci_port_test_fops);
	debugfs_create_file("qheads", S_IRUGO, ci->debugfs, ci,
			    &ci_qheads_fops);
	debugfs_create_file("requests", S_IRUGO, ci->debugfs, ci,
			    &ci_requests_fops);

	if (ci_otg_is_fsm_mode(ci)) {
		debugfs_create_file("otg", S_IRUGO, ci->debugfs, ci,
				    &ci_otg_fops);
	}

	debugfs_create_file("role", S_IRUGO | S_IWUSR, ci->debugfs, ci,
			    &ci_role_fops);
	debugfs_create_file("registers", S_IRUGO, ci->debugfs, ci,
			    &ci_registers_fops);
}