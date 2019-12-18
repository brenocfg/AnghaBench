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
struct sas_ha_struct {struct hisi_hba* lldd_ha; } ;
struct pci_dev {int /*<<< orphan*/  pm_cap; } ;
struct hisi_hba {int /*<<< orphan*/  flags; int /*<<< orphan*/  wq; struct Scsi_Host* shost; struct device* dev; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
typedef  int /*<<< orphan*/  pci_power_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HISI_SAS_REJECT_CMD_BIT ; 
 int /*<<< orphan*/  HISI_SAS_RESET_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 int disable_host_v3_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_init_mem (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_release_tasks (struct hisi_hba*) ; 
 int /*<<< orphan*/  pci_choose_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct sas_ha_struct* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_suspend_ha (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  scsi_block_requests (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_unblock_requests (struct Scsi_Host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_sas_v3_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct sas_ha_struct *sha = pci_get_drvdata(pdev);
	struct hisi_hba *hisi_hba = sha->lldd_ha;
	struct device *dev = hisi_hba->dev;
	struct Scsi_Host *shost = hisi_hba->shost;
	pci_power_t device_state;
	int rc;

	if (!pdev->pm_cap) {
		dev_err(dev, "PCI PM not supported\n");
		return -ENODEV;
	}

	if (test_and_set_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags))
		return -1;

	scsi_block_requests(shost);
	set_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);
	flush_workqueue(hisi_hba->wq);

	rc = disable_host_v3_hw(hisi_hba);
	if (rc) {
		dev_err(dev, "PM suspend: disable host failed rc=%d\n", rc);
		clear_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);
		clear_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags);
		scsi_unblock_requests(shost);
		return rc;
	}

	hisi_sas_init_mem(hisi_hba);

	device_state = pci_choose_state(pdev, state);
	dev_warn(dev, "entering operating state [D%d]\n",
			device_state);
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_power_state(pdev, device_state);

	hisi_sas_release_tasks(hisi_hba);

	sas_suspend_ha(sha);
	return 0;
}