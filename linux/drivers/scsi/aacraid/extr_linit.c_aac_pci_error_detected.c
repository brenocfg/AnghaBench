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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct aac_dev {int handle_pci_error; int /*<<< orphan*/  scsi_host_ptr; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  enum pci_channel_state { ____Placeholder_pci_channel_state } pci_channel_state ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_CAN_RECOVER ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  aac_adapter_ioremap (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_cancel_safw_rescan_worker (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_flush_ios (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_release_resources (struct aac_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
#define  pci_channel_io_frozen 130 
#define  pci_channel_io_normal 129 
#define  pci_channel_io_perm_failure 128 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 struct aac_dev* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static pci_ers_result_t aac_pci_error_detected(struct pci_dev *pdev,
					enum pci_channel_state error)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct aac_dev *aac = shost_priv(shost);

	dev_err(&pdev->dev, "aacraid: PCI error detected %x\n", error);

	switch (error) {
	case pci_channel_io_normal:
		return PCI_ERS_RESULT_CAN_RECOVER;
	case pci_channel_io_frozen:
		aac->handle_pci_error = 1;

		scsi_block_requests(aac->scsi_host_ptr);
		aac_cancel_safw_rescan_worker(aac);
		aac_flush_ios(aac);
		aac_release_resources(aac);

		pci_disable_pcie_error_reporting(pdev);
		aac_adapter_ioremap(aac, 0);

		return PCI_ERS_RESULT_NEED_RESET;
	case pci_channel_io_perm_failure:
		aac->handle_pci_error = 1;

		aac_flush_ios(aac);
		return PCI_ERS_RESULT_DISCONNECT;
	}

	return PCI_ERS_RESULT_NEED_RESET;
}