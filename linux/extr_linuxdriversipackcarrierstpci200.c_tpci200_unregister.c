#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tpci200_board {TYPE_1__* info; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq; } ;
struct TYPE_6__ {TYPE_2__* pdev; int /*<<< orphan*/  cfg_regs; int /*<<< orphan*/  interface_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPCI200_CFG_MEM_BAR ; 
 int /*<<< orphan*/  TPCI200_IO_ID_INT_SPACES_BAR ; 
 int /*<<< orphan*/  TPCI200_IP_INTERFACE_BAR ; 
 int /*<<< orphan*/  TPCI200_MEM16_SPACE_BAR ; 
 int /*<<< orphan*/  TPCI200_MEM8_SPACE_BAR ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pci_dev_put (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_iounmap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tpci200_unregister(struct tpci200_board *tpci200)
{
	free_irq(tpci200->info->pdev->irq, (void *) tpci200);

	pci_iounmap(tpci200->info->pdev, tpci200->info->interface_regs);
	pci_iounmap(tpci200->info->pdev, tpci200->info->cfg_regs);

	pci_release_region(tpci200->info->pdev, TPCI200_IP_INTERFACE_BAR);
	pci_release_region(tpci200->info->pdev, TPCI200_IO_ID_INT_SPACES_BAR);
	pci_release_region(tpci200->info->pdev, TPCI200_MEM16_SPACE_BAR);
	pci_release_region(tpci200->info->pdev, TPCI200_MEM8_SPACE_BAR);
	pci_release_region(tpci200->info->pdev, TPCI200_CFG_MEM_BAR);

	pci_disable_device(tpci200->info->pdev);
	pci_dev_put(tpci200->info->pdev);
}