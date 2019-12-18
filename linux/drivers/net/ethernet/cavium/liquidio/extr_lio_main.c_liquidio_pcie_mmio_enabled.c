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
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 

__attribute__((used)) static pci_ers_result_t liquidio_pcie_mmio_enabled(
				struct pci_dev *pdev __attribute__((unused)))
{
	/* We should never hit this since we never ask for a reset for a Fatal
	 * Error. We always return DISCONNECT in io_error above.
	 * But play safe and return RECOVERED for now.
	 */
	return PCI_ERS_RESULT_RECOVERED;
}