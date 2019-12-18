#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xhci_hcd {int quirks; TYPE_1__* shared_hcd; int /*<<< orphan*/  hcc_params; } ;
struct usb_hcd {int dummy; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct hc_driver {int dummy; } ;
struct TYPE_4__ {int can_do_streams; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HCC_MAX_PSA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int XHCI_BROKEN_STREAMS ; 
 int XHCI_DEFAULT_PM_RUNTIME_ALLOW ; 
 int XHCI_PME_STUCK_QUIRK ; 
 struct usb_hcd* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int usb_add_hcd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* usb_create_shared_hcd (struct hc_driver*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_hcd*) ; 
 int usb_hcd_pci_probe (struct pci_dev*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  usb_hcd_pci_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  usb_put_hcd (TYPE_1__*) ; 
 int xhci_ext_cap_init (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_pme_acpi_rtd3_enable (struct pci_dev*) ; 

__attribute__((used)) static int xhci_pci_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	int retval;
	struct xhci_hcd *xhci;
	struct hc_driver *driver;
	struct usb_hcd *hcd;

	driver = (struct hc_driver *)id->driver_data;

	/* Prevent runtime suspending between USB-2 and USB-3 initialization */
	pm_runtime_get_noresume(&dev->dev);

	/* Register the USB 2.0 roothub.
	 * FIXME: USB core must know to register the USB 2.0 roothub first.
	 * This is sort of silly, because we could just set the HCD driver flags
	 * to say USB 2.0, but I'm not sure what the implications would be in
	 * the other parts of the HCD code.
	 */
	retval = usb_hcd_pci_probe(dev, id);

	if (retval)
		goto put_runtime_pm;

	/* USB 2.0 roothub is stored in the PCI device now. */
	hcd = dev_get_drvdata(&dev->dev);
	xhci = hcd_to_xhci(hcd);
	xhci->shared_hcd = usb_create_shared_hcd(driver, &dev->dev,
				pci_name(dev), hcd);
	if (!xhci->shared_hcd) {
		retval = -ENOMEM;
		goto dealloc_usb2_hcd;
	}

	retval = xhci_ext_cap_init(xhci);
	if (retval)
		goto put_usb3_hcd;

	retval = usb_add_hcd(xhci->shared_hcd, dev->irq,
			IRQF_SHARED);
	if (retval)
		goto put_usb3_hcd;
	/* Roothub already marked as USB 3.0 speed */

	if (!(xhci->quirks & XHCI_BROKEN_STREAMS) &&
			HCC_MAX_PSA(xhci->hcc_params) >= 4)
		xhci->shared_hcd->can_do_streams = 1;

	if (xhci->quirks & XHCI_PME_STUCK_QUIRK)
		xhci_pme_acpi_rtd3_enable(dev);

	/* USB-2 and USB-3 roothubs initialized, allow runtime pm suspend */
	pm_runtime_put_noidle(&dev->dev);

	if (xhci->quirks & XHCI_DEFAULT_PM_RUNTIME_ALLOW)
		pm_runtime_allow(&dev->dev);

	return 0;

put_usb3_hcd:
	usb_put_hcd(xhci->shared_hcd);
dealloc_usb2_hcd:
	usb_hcd_pci_remove(dev);
put_runtime_pm:
	pm_runtime_put_noidle(&dev->dev);
	return retval;
}