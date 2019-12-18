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
struct pci_dev {int dummy; } ;
struct ism_dev {int /*<<< orphan*/  smcd; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_IRQ_MSI ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ism_dev*) ; 
 int /*<<< orphan*/  ism_handle_irq ; 
 int ism_read_local_gid (struct ism_dev*) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  query_info (struct ism_dev*) ; 
 int register_ieq (struct ism_dev*) ; 
 int register_sba (struct ism_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ism_dev*) ; 
 int smcd_register_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_ieq (struct ism_dev*) ; 
 int /*<<< orphan*/  unregister_sba (struct ism_dev*) ; 

__attribute__((used)) static int ism_dev_init(struct ism_dev *ism)
{
	struct pci_dev *pdev = ism->pdev;
	int ret;

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI);
	if (ret <= 0)
		goto out;

	ret = request_irq(pci_irq_vector(pdev, 0), ism_handle_irq, 0,
			  pci_name(pdev), ism);
	if (ret)
		goto free_vectors;

	ret = register_sba(ism);
	if (ret)
		goto free_irq;

	ret = register_ieq(ism);
	if (ret)
		goto unreg_sba;

	ret = ism_read_local_gid(ism);
	if (ret)
		goto unreg_ieq;

	ret = smcd_register_dev(ism->smcd);
	if (ret)
		goto unreg_ieq;

	query_info(ism);
	return 0;

unreg_ieq:
	unregister_ieq(ism);
unreg_sba:
	unregister_sba(ism);
free_irq:
	free_irq(pci_irq_vector(pdev, 0), ism);
free_vectors:
	pci_free_irq_vectors(pdev);
out:
	return ret;
}