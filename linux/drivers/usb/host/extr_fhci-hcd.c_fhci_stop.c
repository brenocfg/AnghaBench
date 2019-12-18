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
struct fhci_hcd {int /*<<< orphan*/ * usb_lld; } ;

/* Variables and functions */
 int /*<<< orphan*/  fhci_mem_free (struct fhci_hcd*) ; 
 int /*<<< orphan*/  fhci_usb_disable (struct fhci_hcd*) ; 
 int /*<<< orphan*/  fhci_usb_disable_interrupt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fhci_usb_free (int /*<<< orphan*/ *) ; 
 struct fhci_hcd* hcd_to_fhci (struct usb_hcd*) ; 

__attribute__((used)) static void fhci_stop(struct usb_hcd *hcd)
{
	struct fhci_hcd *fhci = hcd_to_fhci(hcd);

	fhci_usb_disable_interrupt(fhci->usb_lld);
	fhci_usb_disable(fhci);

	fhci_usb_free(fhci->usb_lld);
	fhci->usb_lld = NULL;
	fhci_mem_free(fhci);
}