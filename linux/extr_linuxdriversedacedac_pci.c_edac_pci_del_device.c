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
struct edac_pci_ctl_info {int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  mod_name; int /*<<< orphan*/  pci_idx; int /*<<< orphan*/  work; scalar_t__ edac_check; int /*<<< orphan*/  op_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_PCI ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  OP_OFFLINE ; 
 int /*<<< orphan*/  del_edac_pci_from_global_list (struct edac_pci_ctl_info*) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_dev_name (struct edac_pci_ctl_info*) ; 
 int /*<<< orphan*/  edac_pci_ctls_mutex ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_stop_work (int /*<<< orphan*/ *) ; 
 struct edac_pci_ctl_info* find_edac_pci_by_dev (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct edac_pci_ctl_info *edac_pci_del_device(struct device *dev)
{
	struct edac_pci_ctl_info *pci;

	edac_dbg(0, "\n");

	mutex_lock(&edac_pci_ctls_mutex);

	/* ensure the control struct is on the global list
	 * if not, then leave
	 */
	pci = find_edac_pci_by_dev(dev);
	if (pci  == NULL) {
		mutex_unlock(&edac_pci_ctls_mutex);
		return NULL;
	}

	pci->op_state = OP_OFFLINE;

	del_edac_pci_from_global_list(pci);

	mutex_unlock(&edac_pci_ctls_mutex);

	if (pci->edac_check)
		edac_stop_work(&pci->work);

	edac_printk(KERN_INFO, EDAC_PCI,
		"Removed device %d for %s %s: DEV %s\n",
		pci->pci_idx, pci->mod_name, pci->ctl_name, edac_dev_name(pci));

	return pci;
}