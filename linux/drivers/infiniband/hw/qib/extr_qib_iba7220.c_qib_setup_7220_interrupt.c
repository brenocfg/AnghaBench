#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qib_devdata {TYPE_1__* pcidev; } ;
struct TYPE_3__ {scalar_t__ msi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_DRV_NAME ; 
 int /*<<< orphan*/  pci_irq_vector (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pci_request_irq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_7220intr ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qib_setup_7220_interrupt(struct qib_devdata *dd)
{
	int ret;

	ret = pci_request_irq(dd->pcidev, 0, qib_7220intr, NULL, dd,
			      QIB_DRV_NAME);
	if (ret)
		qib_dev_err(dd, "Couldn't setup %s interrupt (irq=%d): %d\n",
			    dd->pcidev->msi_enabled ?  "MSI" : "INTx",
			    pci_irq_vector(dd->pcidev, 0), ret);
}