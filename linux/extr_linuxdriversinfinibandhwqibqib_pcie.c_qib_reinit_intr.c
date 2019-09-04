#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct qib_devdata {int msi_data; int flags; TYPE_1__* pcidev; int /*<<< orphan*/  msi_hi; int /*<<< orphan*/  msi_lo; } ;
struct TYPE_5__ {int msi_cap; } ;

/* Variables and functions */
 scalar_t__ PCI_MSI_ADDRESS_HI ; 
 scalar_t__ PCI_MSI_ADDRESS_LO ; 
 int PCI_MSI_FLAGS ; 
 int PCI_MSI_FLAGS_64BIT ; 
 int PCI_MSI_FLAGS_ENABLE ; 
 int QIB_HAS_INTX ; 
 int /*<<< orphan*/  pci_read_config_word (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_write_config_dword (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  qib_free_irq (struct qib_devdata*) ; 

int qib_reinit_intr(struct qib_devdata *dd)
{
	int pos;
	u16 control;
	int ret = 0;

	/* If we aren't using MSI, don't restore it */
	if (!dd->msi_lo)
		goto bail;

	pos = dd->pcidev->msi_cap;
	if (!pos) {
		qib_dev_err(dd,
			"Can't find MSI capability, can't restore MSI settings\n");
		ret = 0;
		/* nothing special for MSIx, just MSI */
		goto bail;
	}
	pci_write_config_dword(dd->pcidev, pos + PCI_MSI_ADDRESS_LO,
			       dd->msi_lo);
	pci_write_config_dword(dd->pcidev, pos + PCI_MSI_ADDRESS_HI,
			       dd->msi_hi);
	pci_read_config_word(dd->pcidev, pos + PCI_MSI_FLAGS, &control);
	if (!(control & PCI_MSI_FLAGS_ENABLE)) {
		control |= PCI_MSI_FLAGS_ENABLE;
		pci_write_config_word(dd->pcidev, pos + PCI_MSI_FLAGS,
				      control);
	}
	/* now rewrite the data (vector) info */
	pci_write_config_word(dd->pcidev, pos +
			      ((control & PCI_MSI_FLAGS_64BIT) ? 12 : 8),
			      dd->msi_data);
	ret = 1;
bail:
	qib_free_irq(dd);

	if (!ret && (dd->flags & QIB_HAS_INTX))
		ret = 1;

	/* and now set the pci master bit again */
	pci_set_master(dd->pcidev);

	return ret;
}