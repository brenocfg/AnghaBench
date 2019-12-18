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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct cobalt {TYPE_2__* pci_dev; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_MLW ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned pcie_bus_link_get_lanes(struct cobalt *cobalt)
{
	struct pci_dev *pci_dev = cobalt->pci_dev->bus->self;
	u32 link;

	if (!pci_is_pcie(pci_dev))
		return 0;
	pcie_capability_read_dword(pci_dev, PCI_EXP_LNKCAP, &link);
	return (link & PCI_EXP_LNKCAP_MLW) >> 4;
}