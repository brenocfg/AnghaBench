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
struct mlxsw_pci {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pci_alloc_irq_vectors (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_pci_alloc_irq_vectors(struct mlxsw_pci *mlxsw_pci)
{
	int err;

	err = pci_alloc_irq_vectors(mlxsw_pci->pdev, 1, 1, PCI_IRQ_MSIX);
	if (err < 0)
		dev_err(&mlxsw_pci->pdev->dev, "MSI-X init failed\n");
	return err;
}