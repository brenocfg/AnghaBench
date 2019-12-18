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
typedef  scalar_t__ u16 ;
struct pci_dev {int dummy; } ;
struct dpc_dev {scalar_t__ rp_extensions; scalar_t__ cap_pos; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 scalar_t__ PCI_EXP_DPC_STATUS ; 
 int /*<<< orphan*/  PCI_EXP_DPC_STATUS_TRIGGER ; 
 scalar_t__ dpc_wait_rp_inactive (struct dpc_dev*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_wait_for_link (struct pci_dev*,int) ; 
 struct dpc_dev* to_dpc_dev (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t dpc_reset_link(struct pci_dev *pdev)
{
	struct dpc_dev *dpc;
	u16 cap;

	/*
	 * DPC disables the Link automatically in hardware, so it has
	 * already been reset by the time we get here.
	 */
	dpc = to_dpc_dev(pdev);
	cap = dpc->cap_pos;

	/*
	 * Wait until the Link is inactive, then clear DPC Trigger Status
	 * to allow the Port to leave DPC.
	 */
	pcie_wait_for_link(pdev, false);

	if (dpc->rp_extensions && dpc_wait_rp_inactive(dpc))
		return PCI_ERS_RESULT_DISCONNECT;

	pci_write_config_word(pdev, cap + PCI_EXP_DPC_STATUS,
			      PCI_EXP_DPC_STATUS_TRIGGER);

	if (!pcie_wait_for_link(pdev, true))
		return PCI_ERS_RESULT_DISCONNECT;

	return PCI_ERS_RESULT_RECOVERED;
}