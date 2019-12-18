#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fwnode_handle {int dummy; } ;
struct altera_msi {int /*<<< orphan*/  inner_domain; TYPE_1__* pdev; int /*<<< orphan*/  msi_domain; int /*<<< orphan*/  num_of_vectors; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  altera_msi_domain_info ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct altera_msi*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_domain_ops ; 
 struct fwnode_handle* of_node_to_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_msi_create_irq_domain (struct fwnode_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int altera_allocate_domains(struct altera_msi *msi)
{
	struct fwnode_handle *fwnode = of_node_to_fwnode(msi->pdev->dev.of_node);

	msi->inner_domain = irq_domain_add_linear(NULL, msi->num_of_vectors,
					     &msi_domain_ops, msi);
	if (!msi->inner_domain) {
		dev_err(&msi->pdev->dev, "failed to create IRQ domain\n");
		return -ENOMEM;
	}

	msi->msi_domain = pci_msi_create_irq_domain(fwnode,
				&altera_msi_domain_info, msi->inner_domain);
	if (!msi->msi_domain) {
		dev_err(&msi->pdev->dev, "failed to create MSI domain\n");
		irq_domain_remove(msi->inner_domain);
		return -ENOMEM;
	}

	return 0;
}