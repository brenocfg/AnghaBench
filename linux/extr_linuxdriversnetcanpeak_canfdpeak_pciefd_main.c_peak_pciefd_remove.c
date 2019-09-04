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
struct pciefd_board {int /*<<< orphan*/  reg_base; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pciefd_board* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pciefd_can_remove_all (struct pciefd_board*) ; 

__attribute__((used)) static void peak_pciefd_remove(struct pci_dev *pdev)
{
	struct pciefd_board *pciefd = pci_get_drvdata(pdev);

	/* release CAN-FD channels resources */
	pciefd_can_remove_all(pciefd);

	pci_iounmap(pdev, pciefd->reg_base);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
}