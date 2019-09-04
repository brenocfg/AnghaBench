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
struct hfi1_devdata {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  int pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_PRESENT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,...) ; 
 int /*<<< orphan*/  hfi1_disable_after_error (struct hfi1_devdata*) ; 
#define  pci_channel_io_frozen 130 
#define  pci_channel_io_normal 129 
#define  pci_channel_io_perm_failure 128 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct hfi1_devdata* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t
pci_error_detected(struct pci_dev *pdev, pci_channel_state_t state)
{
	struct hfi1_devdata *dd = pci_get_drvdata(pdev);
	pci_ers_result_t ret = PCI_ERS_RESULT_RECOVERED;

	switch (state) {
	case pci_channel_io_normal:
		dd_dev_info(dd, "State Normal, ignoring\n");
		break;

	case pci_channel_io_frozen:
		dd_dev_info(dd, "State Frozen, requesting reset\n");
		pci_disable_device(pdev);
		ret = PCI_ERS_RESULT_NEED_RESET;
		break;

	case pci_channel_io_perm_failure:
		if (dd) {
			dd_dev_info(dd, "State Permanent Failure, disabling\n");
			/* no more register accesses! */
			dd->flags &= ~HFI1_PRESENT;
			hfi1_disable_after_error(dd);
		}
		 /* else early, or other problem */
		ret =  PCI_ERS_RESULT_DISCONNECT;
		break;

	default: /* shouldn't happen */
		dd_dev_info(dd, "HFI1 PCI errors detected (state %d)\n",
			    state);
		break;
	}
	return ret;
}