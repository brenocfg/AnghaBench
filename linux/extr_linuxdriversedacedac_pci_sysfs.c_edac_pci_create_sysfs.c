#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct edac_pci_ctl_info {int pci_idx; TYPE_1__* dev; struct kobject kobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_PCI_SYMLINK ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int edac_pci_create_instance_kobj (struct edac_pci_ctl_info*,int) ; 
 int edac_pci_main_kobj_setup () ; 
 int /*<<< orphan*/  edac_pci_main_kobj_teardown () ; 
 int /*<<< orphan*/  edac_pci_unregister_sysfs_instance_kobj (struct edac_pci_ctl_info*) ; 
 int sysfs_create_link (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int edac_pci_create_sysfs(struct edac_pci_ctl_info *pci)
{
	int err;
	struct kobject *edac_kobj = &pci->kobj;

	edac_dbg(0, "idx=%d\n", pci->pci_idx);

	/* create the top main EDAC PCI kobject, IF needed */
	err = edac_pci_main_kobj_setup();
	if (err)
		return err;

	/* Create this instance's kobject under the MAIN kobject */
	err = edac_pci_create_instance_kobj(pci, pci->pci_idx);
	if (err)
		goto unregister_cleanup;

	err = sysfs_create_link(edac_kobj, &pci->dev->kobj, EDAC_PCI_SYMLINK);
	if (err) {
		edac_dbg(0, "sysfs_create_link() returned err= %d\n", err);
		goto symlink_fail;
	}

	return 0;

	/* Error unwind stack */
symlink_fail:
	edac_pci_unregister_sysfs_instance_kobj(pci);

unregister_cleanup:
	edac_pci_main_kobj_teardown();

	return err;
}