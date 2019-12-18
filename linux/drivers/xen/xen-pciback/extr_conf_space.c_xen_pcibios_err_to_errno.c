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

/* Variables and functions */
#define  PCIBIOS_BAD_REGISTER_NUMBER 132 
#define  PCIBIOS_DEVICE_NOT_FOUND 131 
#define  PCIBIOS_FUNC_NOT_SUPPORTED 130 
#define  PCIBIOS_SET_FAILED 129 
#define  PCIBIOS_SUCCESSFUL 128 
 int XEN_PCI_ERR_access_denied ; 
 int XEN_PCI_ERR_dev_not_found ; 
 int XEN_PCI_ERR_invalid_offset ; 
 int XEN_PCI_ERR_not_implemented ; 
 int XEN_PCI_ERR_success ; 

__attribute__((used)) static int xen_pcibios_err_to_errno(int err)
{
	switch (err) {
	case PCIBIOS_SUCCESSFUL:
		return XEN_PCI_ERR_success;
	case PCIBIOS_DEVICE_NOT_FOUND:
		return XEN_PCI_ERR_dev_not_found;
	case PCIBIOS_BAD_REGISTER_NUMBER:
		return XEN_PCI_ERR_invalid_offset;
	case PCIBIOS_FUNC_NOT_SUPPORTED:
		return XEN_PCI_ERR_not_implemented;
	case PCIBIOS_SET_FAILED:
		return XEN_PCI_ERR_access_denied;
	}
	return err;
}