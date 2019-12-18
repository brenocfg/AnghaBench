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
struct TYPE_2__ {int /*<<< orphan*/ * hs_companion; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct pci_dev {scalar_t__ class; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CL_EHCI ; 
 int /*<<< orphan*/  companions_rwsem ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_remove ; 
 int /*<<< orphan*/  for_each_companion (struct pci_dev*,struct usb_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ pci_dev_run_wake (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct usb_hcd* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_hcd_irq (int /*<<< orphan*/ ,struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

void usb_hcd_pci_remove(struct pci_dev *dev)
{
	struct usb_hcd		*hcd;

	hcd = pci_get_drvdata(dev);
	if (!hcd)
		return;

	if (pci_dev_run_wake(dev))
		pm_runtime_get_noresume(&dev->dev);

	/* Fake an interrupt request in order to give the driver a chance
	 * to test whether the controller hardware has been removed (e.g.,
	 * cardbus physical eject).
	 */
	local_irq_disable();
	usb_hcd_irq(0, hcd);
	local_irq_enable();

	/* Note: dev_set_drvdata must be called while holding the rwsem */
	if (dev->class == CL_EHCI) {
		down_write(&companions_rwsem);
		for_each_companion(dev, hcd, ehci_remove);
		usb_remove_hcd(hcd);
		dev_set_drvdata(&dev->dev, NULL);
		up_write(&companions_rwsem);
	} else {
		/* Not EHCI; just clear the companion pointer */
		down_read(&companions_rwsem);
		hcd->self.hs_companion = NULL;
		usb_remove_hcd(hcd);
		dev_set_drvdata(&dev->dev, NULL);
		up_read(&companions_rwsem);
	}
	usb_put_hcd(hcd);
	pci_disable_device(dev);
}