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
typedef  int u64 ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_domain_nr (TYPE_1__*) ; 

__attribute__((used)) static u64
nouveau_pci_name(struct pci_dev *pdev)
{
	u64 name = (u64)pci_domain_nr(pdev->bus) << 32;
	name |= pdev->bus->number << 16;
	name |= PCI_SLOT(pdev->devfn) << 8;
	return name | PCI_FUNC(pdev->devfn);
}