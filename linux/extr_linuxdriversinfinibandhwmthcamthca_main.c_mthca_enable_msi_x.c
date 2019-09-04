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
struct TYPE_3__ {TYPE_2__* eq; } ;
struct mthca_dev {int /*<<< orphan*/  pdev; TYPE_1__ eq_table; } ;
struct TYPE_4__ {void* msi_x_vector; } ;

/* Variables and functions */
 size_t MTHCA_EQ_ASYNC ; 
 size_t MTHCA_EQ_CMD ; 
 size_t MTHCA_EQ_COMP ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 void* pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mthca_enable_msi_x(struct mthca_dev *mdev)
{
	int err;

	err = pci_alloc_irq_vectors(mdev->pdev, 3, 3, PCI_IRQ_MSIX);
	if (err < 0)
		return err;

	mdev->eq_table.eq[MTHCA_EQ_COMP ].msi_x_vector =
			pci_irq_vector(mdev->pdev, 0);
	mdev->eq_table.eq[MTHCA_EQ_ASYNC].msi_x_vector =
			pci_irq_vector(mdev->pdev, 1);
	mdev->eq_table.eq[MTHCA_EQ_CMD  ].msi_x_vector =
			pci_irq_vector(mdev->pdev, 2);

	return 0;
}