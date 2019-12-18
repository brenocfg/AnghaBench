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
struct uhci_hcd {int frame_number; int /*<<< orphan*/  (* configure_hc ) (struct uhci_hcd*) ;int /*<<< orphan*/  frame_dma_handle; } ;

/* Variables and functions */
 int UHCI_MAX_SOF_NUMBER ; 
 int /*<<< orphan*/  USBFLBASEADD ; 
 int /*<<< orphan*/  USBFRNUM ; 
 int /*<<< orphan*/  USBSOF ; 
 int /*<<< orphan*/  USBSOF_DEFAULT ; 
 int /*<<< orphan*/  stub1 (struct uhci_hcd*) ; 
 int /*<<< orphan*/  uhci_writeb (struct uhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhci_writel (struct uhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhci_writew (struct uhci_hcd*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void configure_hc(struct uhci_hcd *uhci)
{
	/* Set the frame length to the default: 1 ms exactly */
	uhci_writeb(uhci, USBSOF_DEFAULT, USBSOF);

	/* Store the frame list base address */
	uhci_writel(uhci, uhci->frame_dma_handle, USBFLBASEADD);

	/* Set the current frame number */
	uhci_writew(uhci, uhci->frame_number & UHCI_MAX_SOF_NUMBER,
			USBFRNUM);

	/* perform any arch/bus specific configuration */
	if (uhci->configure_hc)
		uhci->configure_hc(uhci);
}