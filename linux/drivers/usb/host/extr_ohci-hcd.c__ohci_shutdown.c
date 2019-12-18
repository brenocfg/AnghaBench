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
typedef  int /*<<< orphan*/  u32 ;
struct usb_hcd {int dummy; } ;
struct ohci_hcd {int /*<<< orphan*/  rh_state; TYPE_1__* regs; int /*<<< orphan*/  fminterval; } ;
struct TYPE_2__ {int /*<<< orphan*/  fminterval; int /*<<< orphan*/  cmdstatus; int /*<<< orphan*/  intrdisable; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI_HCR ; 
 int /*<<< orphan*/  OHCI_RH_HALTED ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_readl (struct ohci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_writel (struct ohci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void _ohci_shutdown(struct usb_hcd *hcd)
{
	struct ohci_hcd *ohci;

	ohci = hcd_to_ohci (hcd);
	ohci_writel(ohci, (u32) ~0, &ohci->regs->intrdisable);

	/* Software reset, after which the controller goes into SUSPEND */
	ohci_writel(ohci, OHCI_HCR, &ohci->regs->cmdstatus);
	ohci_readl(ohci, &ohci->regs->cmdstatus);	/* flush the writes */
	udelay(10);

	ohci_writel(ohci, ohci->fminterval, &ohci->regs->fminterval);
	ohci->rh_state = OHCI_RH_HALTED;
}