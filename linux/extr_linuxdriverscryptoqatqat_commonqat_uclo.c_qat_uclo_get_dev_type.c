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
struct icp_qat_fw_loader_handle {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
#define  ADF_C3XXX_PCI_DEVICE_ID 130 
#define  ADF_C62X_PCI_DEVICE_ID 129 
#define  ADF_DH895XCC_PCI_DEVICE_ID 128 
 unsigned int ICP_QAT_AC_895XCC_DEV_TYPE ; 
 unsigned int ICP_QAT_AC_C3XXX_DEV_TYPE ; 
 unsigned int ICP_QAT_AC_C62X_DEV_TYPE ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static unsigned int
qat_uclo_get_dev_type(struct icp_qat_fw_loader_handle *handle)
{
	switch (handle->pci_dev->device) {
	case ADF_DH895XCC_PCI_DEVICE_ID:
		return ICP_QAT_AC_895XCC_DEV_TYPE;
	case ADF_C62X_PCI_DEVICE_ID:
		return ICP_QAT_AC_C62X_DEV_TYPE;
	case ADF_C3XXX_PCI_DEVICE_ID:
		return ICP_QAT_AC_C3XXX_DEV_TYPE;
	default:
		pr_err("QAT: unsupported device 0x%x\n",
		       handle->pci_dev->device);
		return 0;
	}
}