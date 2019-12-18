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
typedef  unsigned long long u64 ;
struct qib_devdata {unsigned long long (* f_portcntr ) (scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ pport; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  QIBPORTCNTR_WORDRCV ; 
 struct qib_devdata* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  qib_devinfo (struct pci_dev*,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 unsigned long long stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pci_ers_result_t
qib_pci_mmio_enabled(struct pci_dev *pdev)
{
	u64 words = 0U;
	struct qib_devdata *dd = pci_get_drvdata(pdev);
	pci_ers_result_t ret = PCI_ERS_RESULT_RECOVERED;

	if (dd && dd->pport) {
		words = dd->f_portcntr(dd->pport, QIBPORTCNTR_WORDRCV);
		if (words == ~0ULL)
			ret = PCI_ERS_RESULT_NEED_RESET;
	}
	qib_devinfo(pdev,
		"QIB mmio_enabled function called, read wordscntr %Lx, returning %d\n",
		words, ret);
	return  ret;
}