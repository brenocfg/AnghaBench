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

__attribute__((used)) static void pnv_pci_ioda_create_dbgfs(void)
{
#ifdef CONFIG_DEBUG_FS
	struct pci_controller *hose, *tmp;
	struct pnv_phb *phb;
	char name[16];

	list_for_each_entry_safe(hose, tmp, &hose_list, list_node) {
		phb = hose->private_data;

		/* Notify initialization of PHB done */
		phb->initialized = 1;

		sprintf(name, "PCI%04x", hose->global_number);
		phb->dbgfs = debugfs_create_dir(name, powerpc_debugfs_root);
		if (!phb->dbgfs) {
			pr_warn("%s: Error on creating debugfs on PHB#%x\n",
				__func__, hose->global_number);
			continue;
		}

		debugfs_create_file("dump_diag_regs", 0200, phb->dbgfs, hose,
				    &pnv_pci_diag_data_fops);
	}
#endif /* CONFIG_DEBUG_FS */
}