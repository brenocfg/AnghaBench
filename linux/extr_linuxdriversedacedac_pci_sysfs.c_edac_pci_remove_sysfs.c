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
struct edac_pci_ctl_info {int /*<<< orphan*/  kobj; int /*<<< orphan*/  pci_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_PCI_SYMLINK ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  edac_pci_main_kobj_teardown () ; 
 int /*<<< orphan*/  edac_pci_unregister_sysfs_instance_kobj (struct edac_pci_ctl_info*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void edac_pci_remove_sysfs(struct edac_pci_ctl_info *pci)
{
	edac_dbg(0, "index=%d\n", pci->pci_idx);

	/* Remove the symlink */
	sysfs_remove_link(&pci->kobj, EDAC_PCI_SYMLINK);

	/* remove this PCI instance's sysfs entries */
	edac_pci_unregister_sysfs_instance_kobj(pci);

	/* Call the main unregister function, which will determine
	 * if this 'pci' is the last instance.
	 * If it is, the main kobject will be unregistered as a result
	 */
	edac_dbg(0, "calling edac_pci_main_kobj_teardown()\n");
	edac_pci_main_kobj_teardown();
}