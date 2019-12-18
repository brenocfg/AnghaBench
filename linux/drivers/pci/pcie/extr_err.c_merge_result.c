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
typedef  int pci_ers_result_t ;
typedef  enum pci_ers_result { ____Placeholder_pci_ers_result } pci_ers_result ;

/* Variables and functions */
#define  PCI_ERS_RESULT_CAN_RECOVER 130 
#define  PCI_ERS_RESULT_DISCONNECT 129 
 int PCI_ERS_RESULT_NEED_RESET ; 
 int PCI_ERS_RESULT_NONE ; 
 int PCI_ERS_RESULT_NO_AER_DRIVER ; 
#define  PCI_ERS_RESULT_RECOVERED 128 

__attribute__((used)) static pci_ers_result_t merge_result(enum pci_ers_result orig,
				  enum pci_ers_result new)
{
	if (new == PCI_ERS_RESULT_NO_AER_DRIVER)
		return PCI_ERS_RESULT_NO_AER_DRIVER;

	if (new == PCI_ERS_RESULT_NONE)
		return orig;

	switch (orig) {
	case PCI_ERS_RESULT_CAN_RECOVER:
	case PCI_ERS_RESULT_RECOVERED:
		orig = new;
		break;
	case PCI_ERS_RESULT_DISCONNECT:
		if (new == PCI_ERS_RESULT_NEED_RESET)
			orig = PCI_ERS_RESULT_NEED_RESET;
		break;
	default:
		break;
	}

	return orig;
}