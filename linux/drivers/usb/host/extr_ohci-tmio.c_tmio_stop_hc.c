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
typedef  int u16 ;
struct usb_hcd {int dummy; } ;
struct tmio_hcd {scalar_t__ ccr; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ohci_hcd {int num_ports; } ;

/* Variables and functions */
 scalar_t__ CCR_BASE ; 
 scalar_t__ CCR_ILME ; 
 scalar_t__ CCR_INTC ; 
 scalar_t__ CCR_PM ; 
 int CCR_PM_CKRNEN ; 
 int CCR_PM_GKEN ; 
 int CCR_PM_USBPW1 ; 
 int CCR_PM_USBPW2 ; 
 int CCR_PM_USBPW3 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 struct tmio_hcd* hcd_to_tmio (struct usb_hcd*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tmio_iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tmio_stop_hc(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);
	struct ohci_hcd *ohci = hcd_to_ohci(hcd);
	struct tmio_hcd *tmio = hcd_to_tmio(hcd);
	u16 pm;

	pm = CCR_PM_GKEN | CCR_PM_CKRNEN;
	switch (ohci->num_ports) {
		default:
			dev_err(&dev->dev, "Unsupported amount of ports: %d\n", ohci->num_ports);
			/* fall through */
		case 3:
			pm |= CCR_PM_USBPW3;
			/* fall through */
		case 2:
			pm |= CCR_PM_USBPW2;
			/* fall through */
		case 1:
			pm |= CCR_PM_USBPW1;
	}
	tmio_iowrite8(0, tmio->ccr + CCR_INTC);
	tmio_iowrite8(0, tmio->ccr + CCR_ILME);
	tmio_iowrite16(0, tmio->ccr + CCR_BASE);
	tmio_iowrite16(0, tmio->ccr + CCR_BASE + 2);
	tmio_iowrite16(pm, tmio->ccr + CCR_PM);
}