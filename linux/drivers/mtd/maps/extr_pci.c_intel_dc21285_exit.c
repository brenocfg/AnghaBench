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
struct map_pci_info {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_rom (struct pci_dev*) ; 

__attribute__((used)) static void
intel_dc21285_exit(struct pci_dev *dev, struct map_pci_info *map)
{
	if (map->base)
		iounmap(map->base);

	/*
	 * We need to undo the PCI BAR2/PCI ROM BAR address alteration.
	 */
	pci_disable_rom(dev);
}