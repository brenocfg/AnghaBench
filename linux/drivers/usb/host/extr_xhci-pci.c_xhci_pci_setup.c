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
struct xhci_hcd {int imod_interval; scalar_t__ sbrn; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XHCI_SBRN_OFFSET ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_is_primary_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,unsigned int) ; 
 int xhci_gen_setup (struct usb_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_pci_quirks ; 
 int xhci_pci_reinit (struct xhci_hcd*,struct pci_dev*) ; 

__attribute__((used)) static int xhci_pci_setup(struct usb_hcd *hcd)
{
	struct xhci_hcd		*xhci;
	struct pci_dev		*pdev = to_pci_dev(hcd->self.controller);
	int			retval;

	xhci = hcd_to_xhci(hcd);
	if (!xhci->sbrn)
		pci_read_config_byte(pdev, XHCI_SBRN_OFFSET, &xhci->sbrn);

	/* imod_interval is the interrupt moderation value in nanoseconds. */
	xhci->imod_interval = 40000;

	retval = xhci_gen_setup(hcd, xhci_pci_quirks);
	if (retval)
		return retval;

	if (!usb_hcd_is_primary_hcd(hcd))
		return 0;

	xhci_dbg(xhci, "Got SBRN %u\n", (unsigned int) xhci->sbrn);

	/* Find any debug ports */
	return xhci_pci_reinit(xhci, pdev);
}