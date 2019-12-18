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
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_FUNC_NOT_SUPPORTED ; 
 int PCIBIOS_SET_FAILED ; 
 int PCIBIOS_SUCCESSFUL ; 
#define  XEN_PCI_ERR_access_denied 133 
#define  XEN_PCI_ERR_dev_not_found 132 
#define  XEN_PCI_ERR_invalid_offset 131 
#define  XEN_PCI_ERR_not_implemented 130 
#define  XEN_PCI_ERR_op_failed 129 
#define  XEN_PCI_ERR_success 128 

__attribute__((used)) static int errno_to_pcibios_err(int errno)
{
	switch (errno) {
	case XEN_PCI_ERR_success:
		return PCIBIOS_SUCCESSFUL;

	case XEN_PCI_ERR_dev_not_found:
		return PCIBIOS_DEVICE_NOT_FOUND;

	case XEN_PCI_ERR_invalid_offset:
	case XEN_PCI_ERR_op_failed:
		return PCIBIOS_BAD_REGISTER_NUMBER;

	case XEN_PCI_ERR_not_implemented:
		return PCIBIOS_FUNC_NOT_SUPPORTED;

	case XEN_PCI_ERR_access_denied:
		return PCIBIOS_SET_FAILED;
	}
	return errno;
}