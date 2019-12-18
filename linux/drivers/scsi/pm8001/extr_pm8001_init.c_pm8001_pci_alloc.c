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
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct pm8001_hba_info {size_t chip_id; int logging_level; int /*<<< orphan*/ * irq_vector; int /*<<< orphan*/ * tasklet; int /*<<< orphan*/  iomb_size; int /*<<< orphan*/  name; scalar_t__ id; struct Scsi_Host* shost; struct sas_ha_struct* sas; int /*<<< orphan*/  irq; int /*<<< orphan*/ * chip; int /*<<< orphan*/ * dev; struct pci_dev* pdev; } ;
struct pci_device_id {size_t driver_data; } ;
struct pci_dev {int /*<<< orphan*/  msix_cap; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 char* DRV_NAME ; 
 int /*<<< orphan*/  IOMB_SIZE_SPC ; 
 int /*<<< orphan*/  IOMB_SIZE_SPCV ; 
 int PM8001_MAX_MSIX_VEC ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 size_t chip_8001 ; 
 int /*<<< orphan*/  pci_msi_enabled () ; 
 int /*<<< orphan*/  pm8001_alloc (struct pm8001_hba_info*,struct pci_device_id const*) ; 
 int /*<<< orphan*/ * pm8001_chips ; 
 int /*<<< orphan*/  pm8001_free (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  pm8001_id ; 
 int /*<<< orphan*/  pm8001_ioremap (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  pm8001_tasklet ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static struct pm8001_hba_info *pm8001_pci_alloc(struct pci_dev *pdev,
				 const struct pci_device_id *ent,
				struct Scsi_Host *shost)

{
	struct pm8001_hba_info *pm8001_ha;
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	int j;

	pm8001_ha = sha->lldd_ha;
	if (!pm8001_ha)
		return NULL;

	pm8001_ha->pdev = pdev;
	pm8001_ha->dev = &pdev->dev;
	pm8001_ha->chip_id = ent->driver_data;
	pm8001_ha->chip = &pm8001_chips[pm8001_ha->chip_id];
	pm8001_ha->irq = pdev->irq;
	pm8001_ha->sas = sha;
	pm8001_ha->shost = shost;
	pm8001_ha->id = pm8001_id++;
	pm8001_ha->logging_level = 0x01;
	sprintf(pm8001_ha->name, "%s%d", DRV_NAME, pm8001_ha->id);
	/* IOMB size is 128 for 8088/89 controllers */
	if (pm8001_ha->chip_id != chip_8001)
		pm8001_ha->iomb_size = IOMB_SIZE_SPCV;
	else
		pm8001_ha->iomb_size = IOMB_SIZE_SPC;

#ifdef PM8001_USE_TASKLET
	/* Tasklet for non msi-x interrupt handler */
	if ((!pdev->msix_cap || !pci_msi_enabled())
	    || (pm8001_ha->chip_id == chip_8001))
		tasklet_init(&pm8001_ha->tasklet[0], pm8001_tasklet,
			(unsigned long)&(pm8001_ha->irq_vector[0]));
	else
		for (j = 0; j < PM8001_MAX_MSIX_VEC; j++)
			tasklet_init(&pm8001_ha->tasklet[j], pm8001_tasklet,
				(unsigned long)&(pm8001_ha->irq_vector[j]));
#endif
	pm8001_ioremap(pm8001_ha);
	if (!pm8001_alloc(pm8001_ha, ent))
		return pm8001_ha;
	pm8001_free(pm8001_ha);
	return NULL;
}