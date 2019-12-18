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
struct qib_devdata {int /*<<< orphan*/  pcidev; TYPE_1__* cspec; int /*<<< orphan*/  revision; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ChipRevMinor ; 
 int /*<<< orphan*/  GPIO_ERRINTR_MASK ; 
 int /*<<< orphan*/  QIB_DRV_NAME ; 
 int /*<<< orphan*/  Revision_R ; 
 int SYM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kr_gpio_mask ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_6120intr ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qib_setup_6120_interrupt(struct qib_devdata *dd)
{
	int ret;

	/*
	 * If the chip supports added error indication via GPIO pins,
	 * enable interrupts on those bits so the interrupt routine
	 * can count the events. Also set flag so interrupt routine
	 * can know they are expected.
	 */
	if (SYM_FIELD(dd->revision, Revision_R,
		      ChipRevMinor) > 1) {
		/* Rev2+ reports extra errors via internal GPIO pins */
		dd->cspec->gpio_mask |= GPIO_ERRINTR_MASK;
		qib_write_kreg(dd, kr_gpio_mask, dd->cspec->gpio_mask);
	}

	ret = pci_request_irq(dd->pcidev, 0, qib_6120intr, NULL, dd,
			      QIB_DRV_NAME);
	if (ret)
		qib_dev_err(dd,
			    "Couldn't setup interrupt (irq=%d): %d\n",
			    pci_irq_vector(dd->pcidev, 0), ret);
}