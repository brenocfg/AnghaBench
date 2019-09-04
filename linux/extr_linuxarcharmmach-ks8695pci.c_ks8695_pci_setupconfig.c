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

/* Variables and functions */
 scalar_t__ KS8695_PBCA ; 
 scalar_t__ KS8695_PCI_VA ; 
 unsigned int PBCA_ENABLE ; 
 unsigned long PBCA_TYPE1 ; 
 int PCI_FUNC (unsigned int) ; 
 int PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void ks8695_pci_setupconfig(unsigned int bus_nr, unsigned int devfn, unsigned int where)
{
	unsigned long pbca;

	pbca = PBCA_ENABLE | (where & ~3);
	pbca |= PCI_SLOT(devfn) << 11 ;
	pbca |= PCI_FUNC(devfn) << 8;
	pbca |= bus_nr << 16;

	if (bus_nr == 0) {
		/* use Type-0 transaction */
		__raw_writel(pbca, KS8695_PCI_VA + KS8695_PBCA);
	} else {
		/* use Type-1 transaction */
		__raw_writel(pbca | PBCA_TYPE1, KS8695_PCI_VA + KS8695_PBCA);
	}
}