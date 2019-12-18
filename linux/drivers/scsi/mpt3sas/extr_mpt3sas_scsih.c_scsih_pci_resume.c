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
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  shost; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*) ; 
 int /*<<< orphan*/  mpt3sas_base_start_watchdog (struct MPT3SAS_ADAPTER*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static void
scsih_pci_resume(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	ioc_info(ioc, "PCI error: resume callback!!\n");

	mpt3sas_base_start_watchdog(ioc);
	scsi_unblock_requests(ioc->shost);
}