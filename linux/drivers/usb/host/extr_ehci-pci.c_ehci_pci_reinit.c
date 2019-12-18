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
struct pci_dev {int dummy; } ;
struct ehci_hcd {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  intel_quark_x1000_insnreg01; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_QUARK_X1000_EHCI_MAX_THRESHOLD ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*) ; 
 int /*<<< orphan*/  ehci_writel (struct ehci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_intel_quark_x1000 (struct pci_dev*) ; 
 int pci_set_mwi (struct pci_dev*) ; 

__attribute__((used)) static int ehci_pci_reinit(struct ehci_hcd *ehci, struct pci_dev *pdev)
{
	int			retval;

	/* we expect static quirk code to handle the "extended capabilities"
	 * (currently just BIOS handoff) allowed starting with EHCI 0.96
	 */

	/* PCI Memory-Write-Invalidate cycle support is optional (uncommon) */
	retval = pci_set_mwi(pdev);
	if (!retval)
		ehci_dbg(ehci, "MWI active\n");

	/* Reset the threshold limit */
	if (is_intel_quark_x1000(pdev)) {
		/*
		 * For the Intel QUARK X1000, raise the I/O threshold to the
		 * maximum usable value in order to improve performance.
		 */
		ehci_writel(ehci, INTEL_QUARK_X1000_EHCI_MAX_THRESHOLD,
			ehci->regs->intel_quark_x1000_insnreg01);
	}

	return 0;
}