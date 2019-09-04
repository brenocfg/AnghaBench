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
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  mod_name; int /*<<< orphan*/  mc_idx; int /*<<< orphan*/  work; scalar_t__ edac_check; int /*<<< orphan*/  op_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_MC ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  OP_OFFLINE ; 
 struct mem_ctl_info* __find_mci_by_dev (struct device*) ; 
 scalar_t__ del_mc_from_global_list (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_dev_name (struct mem_ctl_info*) ; 
 int /*<<< orphan*/ * edac_mc_owner ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_remove_sysfs_mci_device (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  edac_stop_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_ctls_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct mem_ctl_info *edac_mc_del_mc(struct device *dev)
{
	struct mem_ctl_info *mci;

	edac_dbg(0, "\n");

	mutex_lock(&mem_ctls_mutex);

	/* find the requested mci struct in the global list */
	mci = __find_mci_by_dev(dev);
	if (mci == NULL) {
		mutex_unlock(&mem_ctls_mutex);
		return NULL;
	}

	/* mark MCI offline: */
	mci->op_state = OP_OFFLINE;

	if (del_mc_from_global_list(mci))
		edac_mc_owner = NULL;

	mutex_unlock(&mem_ctls_mutex);

	if (mci->edac_check)
		edac_stop_work(&mci->work);

	/* remove from sysfs */
	edac_remove_sysfs_mci_device(mci);

	edac_printk(KERN_INFO, EDAC_MC,
		"Removed device %d for %s %s: DEV %s\n", mci->mc_idx,
		mci->mod_name, mci->ctl_name, edac_dev_name(mci));

	return mci;
}