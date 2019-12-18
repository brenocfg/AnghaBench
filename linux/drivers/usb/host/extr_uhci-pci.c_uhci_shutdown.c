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
struct usb_hcd {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hcd_to_uhci (struct usb_hcd*) ; 
 struct usb_hcd* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  uhci_hc_died (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uhci_shutdown(struct pci_dev *pdev)
{
	struct usb_hcd *hcd = pci_get_drvdata(pdev);

	uhci_hc_died(hcd_to_uhci(hcd));
}