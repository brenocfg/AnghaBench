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
struct usb_hcd {int dummy; } ;
struct ehci_hcd {TYPE_1__* regs; scalar_t__ has_hostpc; } ;
struct TYPE_2__ {int /*<<< orphan*/  txfill_tuning; } ;

/* Variables and functions */
 int ehci_setup (struct usb_hcd*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int,int /*<<< orphan*/ *) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 

__attribute__((used)) static int tegra_ehci_reset(struct usb_hcd *hcd)
{
	struct ehci_hcd *ehci = hcd_to_ehci(hcd);
	int retval;
	int txfifothresh;

	retval = ehci_setup(hcd);
	if (retval)
		return retval;

	/*
	 * We should really pull this value out of tegra_ehci_soc_config, but
	 * to avoid needing access to it, make use of the fact that Tegra20 is
	 * the only one so far that needs a value of 10, and Tegra20 is the
	 * only one which doesn't set has_hostpc.
	 */
	txfifothresh = ehci->has_hostpc ? 0x10 : 10;
	ehci_writel(ehci, txfifothresh << 16, &ehci->regs->txfill_tuning);

	return 0;
}