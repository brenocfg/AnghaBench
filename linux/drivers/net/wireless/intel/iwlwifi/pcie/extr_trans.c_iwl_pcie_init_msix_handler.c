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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct msix_entry {int /*<<< orphan*/  vector; } ;
struct iwl_trans_pcie {int alloc_vecs; int def_irq; int /*<<< orphan*/  trans; struct msix_entry* msix_entries; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IWL_ERR (int /*<<< orphan*/ ,char*,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct msix_entry*) ; 
 int /*<<< orphan*/  iwl_pcie_irq_msix_handler ; 
 int /*<<< orphan*/  iwl_pcie_irq_rx_msix_handler ; 
 int /*<<< orphan*/  iwl_pcie_irq_set_affinity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_msix_isr ; 
 char* queue_name (int /*<<< orphan*/ *,struct iwl_trans_pcie*,int) ; 

__attribute__((used)) static int iwl_pcie_init_msix_handler(struct pci_dev *pdev,
				      struct iwl_trans_pcie *trans_pcie)
{
	int i;

	for (i = 0; i < trans_pcie->alloc_vecs; i++) {
		int ret;
		struct msix_entry *msix_entry;
		const char *qname = queue_name(&pdev->dev, trans_pcie, i);

		if (!qname)
			return -ENOMEM;

		msix_entry = &trans_pcie->msix_entries[i];
		ret = devm_request_threaded_irq(&pdev->dev,
						msix_entry->vector,
						iwl_pcie_msix_isr,
						(i == trans_pcie->def_irq) ?
						iwl_pcie_irq_msix_handler :
						iwl_pcie_irq_rx_msix_handler,
						IRQF_SHARED,
						qname,
						msix_entry);
		if (ret) {
			IWL_ERR(trans_pcie->trans,
				"Error allocating IRQ %d\n", i);

			return ret;
		}
	}
	iwl_pcie_irq_set_affinity(trans_pcie->trans);

	return 0;
}