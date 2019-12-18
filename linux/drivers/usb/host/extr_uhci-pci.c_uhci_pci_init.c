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
struct usb_hcd {scalar_t__ rsrc_start; } ;
struct uhci_hcd {unsigned long io_addr; int oc_low; int wait_for_hp; int /*<<< orphan*/  global_suspend_mode_is_broken; int /*<<< orphan*/  resume_detect_interrupts_are_broken; int /*<<< orphan*/  configure_hc; int /*<<< orphan*/  check_and_reset_hc; int /*<<< orphan*/  reset_hc; int /*<<< orphan*/  rh_numports; } ;
struct TYPE_2__ {scalar_t__ vendor; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_HP ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 scalar_t__ PCI_VENDOR_ID_VIA ; 
 int /*<<< orphan*/  check_and_reset_hc (struct uhci_hcd*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ ,int) ; 
 struct uhci_hcd* hcd_to_uhci (struct usb_hcd*) ; 
 TYPE_1__* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhci_count_ports (struct usb_hcd*) ; 
 int /*<<< orphan*/  uhci_dev (struct uhci_hcd*) ; 
 int /*<<< orphan*/  uhci_pci_check_and_reset_hc ; 
 int /*<<< orphan*/  uhci_pci_configure_hc ; 
 int /*<<< orphan*/  uhci_pci_global_suspend_mode_is_broken ; 
 int /*<<< orphan*/  uhci_pci_reset_hc ; 
 int /*<<< orphan*/  uhci_pci_resume_detect_interrupts_are_broken ; 

__attribute__((used)) static int uhci_pci_init(struct usb_hcd *hcd)
{
	struct uhci_hcd *uhci = hcd_to_uhci(hcd);

	uhci->io_addr = (unsigned long) hcd->rsrc_start;

	uhci->rh_numports = uhci_count_ports(hcd);

	/* Intel controllers report the OverCurrent bit active on.
	 * VIA controllers report it active off, so we'll adjust the
	 * bit value.  (It's not standardized in the UHCI spec.)
	 */
	if (to_pci_dev(uhci_dev(uhci))->vendor == PCI_VENDOR_ID_VIA)
		uhci->oc_low = 1;

	/* HP's server management chip requires a longer port reset delay. */
	if (to_pci_dev(uhci_dev(uhci))->vendor == PCI_VENDOR_ID_HP)
		uhci->wait_for_hp = 1;

	/* Intel controllers use non-PME wakeup signalling */
	if (to_pci_dev(uhci_dev(uhci))->vendor == PCI_VENDOR_ID_INTEL)
		device_set_wakeup_capable(uhci_dev(uhci), true);

	/* Set up pointers to PCI-specific functions */
	uhci->reset_hc = uhci_pci_reset_hc;
	uhci->check_and_reset_hc = uhci_pci_check_and_reset_hc;
	uhci->configure_hc = uhci_pci_configure_hc;
	uhci->resume_detect_interrupts_are_broken =
		uhci_pci_resume_detect_interrupts_are_broken;
	uhci->global_suspend_mode_is_broken =
		uhci_pci_global_suspend_mode_is_broken;


	/* Kick BIOS off this hardware and reset if the controller
	 * isn't already safely quiescent.
	 */
	check_and_reset_hc(uhci);
	return 0;
}