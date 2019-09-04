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
struct punit_device {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct punit_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  punit_dbg_file ; 
 int /*<<< orphan*/  punit_dev_state_fops ; 

__attribute__((used)) static int punit_dbgfs_register(struct punit_device *punit_device)
{
	static struct dentry *dev_state;

	punit_dbg_file = debugfs_create_dir("punit_atom", NULL);
	if (!punit_dbg_file)
		return -ENXIO;

	dev_state = debugfs_create_file("dev_power_state", 0444,
					punit_dbg_file, punit_device,
					&punit_dev_state_fops);
	if (!dev_state) {
		pr_err("punit_dev_state register failed\n");
		debugfs_remove(punit_dbg_file);
		return -ENXIO;
	}

	return 0;
}