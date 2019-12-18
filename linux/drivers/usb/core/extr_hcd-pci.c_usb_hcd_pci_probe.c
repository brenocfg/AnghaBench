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
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int amd_resume_bug; TYPE_1__ self; void* rsrc_len; void* rsrc_start; int /*<<< orphan*/ * regs; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int irq; scalar_t__ class; int /*<<< orphan*/  dev; } ;
struct hc_driver {int flags; int /*<<< orphan*/  description; } ;

/* Variables and functions */
 scalar_t__ CL_EHCI ; 
 int EBUSY ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int HCD_MASK ; 
 int HCD_MEMORY ; 
 int HCD_USB11 ; 
 int HCD_USB3 ; 
 int IORESOURCE_IO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  companions_rwsem ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct usb_hcd*) ; 
 int /*<<< orphan*/  device_wakeup_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_ioremap_nocache (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  devm_request_mem_region (int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_request_region (int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_post_add ; 
 int /*<<< orphan*/  ehci_pre_add ; 
 int /*<<< orphan*/  for_each_companion (struct pci_dev*,struct usb_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  non_ehci_add ; 
 scalar_t__ pci_dev_run_wake (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 void* pci_resource_len (struct pci_dev*,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_disabled () ; 
 scalar_t__ usb_hcd_amd_remote_wakeup_quirk (struct pci_dev*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

int usb_hcd_pci_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct hc_driver	*driver;
	struct usb_hcd		*hcd;
	int			retval;
	int			hcd_irq = 0;

	if (usb_disabled())
		return -ENODEV;

	if (!id)
		return -EINVAL;
	driver = (struct hc_driver *)id->driver_data;
	if (!driver)
		return -EINVAL;

	if (pci_enable_device(dev) < 0)
		return -ENODEV;

	/*
	 * The xHCI driver has its own irq management
	 * make sure irq setup is not touched for xhci in generic hcd code
	 */
	if ((driver->flags & HCD_MASK) < HCD_USB3) {
		if (!dev->irq) {
			dev_err(&dev->dev,
			"Found HC with no IRQ. Check BIOS/PCI %s setup!\n",
				pci_name(dev));
			retval = -ENODEV;
			goto disable_pci;
		}
		hcd_irq = dev->irq;
	}

	hcd = usb_create_hcd(driver, &dev->dev, pci_name(dev));
	if (!hcd) {
		retval = -ENOMEM;
		goto disable_pci;
	}

	hcd->amd_resume_bug = (usb_hcd_amd_remote_wakeup_quirk(dev) &&
			driver->flags & (HCD_USB11 | HCD_USB3)) ? 1 : 0;

	if (driver->flags & HCD_MEMORY) {
		/* EHCI, OHCI */
		hcd->rsrc_start = pci_resource_start(dev, 0);
		hcd->rsrc_len = pci_resource_len(dev, 0);
		if (!devm_request_mem_region(&dev->dev, hcd->rsrc_start,
				hcd->rsrc_len, driver->description)) {
			dev_dbg(&dev->dev, "controller already in use\n");
			retval = -EBUSY;
			goto put_hcd;
		}
		hcd->regs = devm_ioremap_nocache(&dev->dev, hcd->rsrc_start,
				hcd->rsrc_len);
		if (hcd->regs == NULL) {
			dev_dbg(&dev->dev, "error mapping memory\n");
			retval = -EFAULT;
			goto put_hcd;
		}

	} else {
		/* UHCI */
		int	region;

		for (region = 0; region < PCI_ROM_RESOURCE; region++) {
			if (!(pci_resource_flags(dev, region) &
					IORESOURCE_IO))
				continue;

			hcd->rsrc_start = pci_resource_start(dev, region);
			hcd->rsrc_len = pci_resource_len(dev, region);
			if (devm_request_region(&dev->dev, hcd->rsrc_start,
					hcd->rsrc_len, driver->description))
				break;
		}
		if (region == PCI_ROM_RESOURCE) {
			dev_dbg(&dev->dev, "no i/o regions available\n");
			retval = -EBUSY;
			goto put_hcd;
		}
	}

	pci_set_master(dev);

	/* Note: dev_set_drvdata must be called while holding the rwsem */
	if (dev->class == CL_EHCI) {
		down_write(&companions_rwsem);
		dev_set_drvdata(&dev->dev, hcd);
		for_each_companion(dev, hcd, ehci_pre_add);
		retval = usb_add_hcd(hcd, hcd_irq, IRQF_SHARED);
		if (retval != 0)
			dev_set_drvdata(&dev->dev, NULL);
		for_each_companion(dev, hcd, ehci_post_add);
		up_write(&companions_rwsem);
	} else {
		down_read(&companions_rwsem);
		dev_set_drvdata(&dev->dev, hcd);
		retval = usb_add_hcd(hcd, hcd_irq, IRQF_SHARED);
		if (retval != 0)
			dev_set_drvdata(&dev->dev, NULL);
		else
			for_each_companion(dev, hcd, non_ehci_add);
		up_read(&companions_rwsem);
	}

	if (retval != 0)
		goto put_hcd;
	device_wakeup_enable(hcd->self.controller);

	if (pci_dev_run_wake(dev))
		pm_runtime_put_noidle(&dev->dev);
	return retval;

put_hcd:
	usb_put_hcd(hcd);
disable_pci:
	pci_disable_device(dev);
	dev_err(&dev->dev, "init %s fail, %d\n", pci_name(dev), retval);
	return retval;
}