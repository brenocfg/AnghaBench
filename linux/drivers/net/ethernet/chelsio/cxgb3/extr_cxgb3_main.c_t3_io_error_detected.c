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
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 struct adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  t3_adapter_error (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pci_ers_result_t t3_io_error_detected(struct pci_dev *pdev,
					     pci_channel_state_t state)
{
	struct adapter *adapter = pci_get_drvdata(pdev);

	if (state == pci_channel_io_perm_failure)
		return PCI_ERS_RESULT_DISCONNECT;

	t3_adapter_error(adapter, 0, 0);

	/* Request a slot reset. */
	return PCI_ERS_RESULT_NEED_RESET;
}