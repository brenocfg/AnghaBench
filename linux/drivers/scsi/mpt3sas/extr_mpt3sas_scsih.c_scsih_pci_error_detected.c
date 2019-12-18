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
struct Scsi_Host {int dummy; } ;
struct MPT3SAS_ADAPTER {int pci_error_recovery; int /*<<< orphan*/  shost; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  int /*<<< orphan*/  pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_CAN_RECOVER ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  _scsih_flush_running_cmds (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt3sas_base_free_resources (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  mpt3sas_base_stop_watchdog (struct MPT3SAS_ADAPTER*) ; 
#define  pci_channel_io_frozen 130 
#define  pci_channel_io_normal 129 
#define  pci_channel_io_perm_failure 128 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static pci_ers_result_t
scsih_pci_error_detected(struct pci_dev *pdev, pci_channel_state_t state)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	ioc_info(ioc, "PCI error: detected callback, state(%d)!!\n", state);

	switch (state) {
	case pci_channel_io_normal:
		return PCI_ERS_RESULT_CAN_RECOVER;
	case pci_channel_io_frozen:
		/* Fatal error, prepare for slot reset */
		ioc->pci_error_recovery = 1;
		scsi_block_requests(ioc->shost);
		mpt3sas_base_stop_watchdog(ioc);
		mpt3sas_base_free_resources(ioc);
		return PCI_ERS_RESULT_NEED_RESET;
	case pci_channel_io_perm_failure:
		/* Permanent error, prepare for device removal */
		ioc->pci_error_recovery = 1;
		mpt3sas_base_stop_watchdog(ioc);
		_scsih_flush_running_cmds(ioc);
		return PCI_ERS_RESULT_DISCONNECT;
	}
	return PCI_ERS_RESULT_NEED_RESET;
}