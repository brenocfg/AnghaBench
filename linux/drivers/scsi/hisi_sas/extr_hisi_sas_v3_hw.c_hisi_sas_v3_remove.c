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
struct TYPE_2__ {struct Scsi_Host* shost; } ;
struct sas_ha_struct {TYPE_1__ core; struct hisi_hba* lldd_ha; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct hisi_hba {int /*<<< orphan*/  timer; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct sas_ha_struct* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hisi_sas_debugfs_exit (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_free (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_kill_tasklets (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_v3_destroy_irqs (struct pci_dev*,struct hisi_hba*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  sas_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sas_unregister_ha (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hisi_sas_v3_remove(struct pci_dev *pdev)
{
	struct device *dev = &pdev->dev;
	struct sas_ha_struct *sha = dev_get_drvdata(dev);
	struct hisi_hba *hisi_hba = sha->lldd_ha;
	struct Scsi_Host *shost = sha->core.shost;

	hisi_sas_debugfs_exit(hisi_hba);

	if (timer_pending(&hisi_hba->timer))
		del_timer(&hisi_hba->timer);

	sas_unregister_ha(sha);
	sas_remove_host(sha->core.shost);

	hisi_sas_v3_destroy_irqs(pdev, hisi_hba);
	hisi_sas_kill_tasklets(hisi_hba);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	hisi_sas_free(hisi_hba);
	scsi_host_put(shost);
}