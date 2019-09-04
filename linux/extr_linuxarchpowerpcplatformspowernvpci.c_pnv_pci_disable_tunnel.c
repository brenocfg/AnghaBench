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
struct pnv_ioda_pe {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct pnv_ioda_pe* pnv_ioda_get_pe (struct pci_dev*) ; 
 int /*<<< orphan*/  pnv_pci_ioda2_set_bypass (struct pnv_ioda_pe*,int) ; 

int pnv_pci_disable_tunnel(struct pci_dev *dev)
{
	struct pnv_ioda_pe *pe;

	pe = pnv_ioda_get_pe(dev);
	if (!pe)
		return -ENODEV;

	/* Restore default real window size. */
	pnv_pci_ioda2_set_bypass(pe, true);
	return 0;
}