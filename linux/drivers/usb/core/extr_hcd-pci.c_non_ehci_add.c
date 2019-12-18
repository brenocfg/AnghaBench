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
struct TYPE_2__ {struct TYPE_2__* hs_companion; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct pci_dev {scalar_t__ class; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CL_EHCI ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ is_ohci_or_uhci (struct pci_dev*) ; 

__attribute__((used)) static void non_ehci_add(struct pci_dev *pdev, struct usb_hcd *hcd,
		struct pci_dev *companion, struct usb_hcd *companion_hcd)
{
	if (is_ohci_or_uhci(pdev) && companion->class == CL_EHCI) {
		dev_dbg(&pdev->dev, "FS/LS companion for %s\n",
				dev_name(&companion->dev));
		hcd->self.hs_companion = &companion_hcd->self;
	}
}