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
struct lpfc_vport {scalar_t__ port_type; int /*<<< orphan*/  listentry; int /*<<< orphan*/  fc_vport; int /*<<< orphan*/  load_flag; struct lpfc_hba* phba; } ;
struct lpfc_hba {int max_vports; int /*<<< orphan*/  port_list_lock; scalar_t__ cfg_xri_rebalancing; int /*<<< orphan*/  hbalock; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_UNLOADING ; 
 scalar_t__ LPFC_PHYSICAL_PORT ; 
 int /*<<< orphan*/  fc_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  fc_vport_terminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_cleanup (struct lpfc_vport*) ; 
 struct lpfc_vport** lpfc_create_vport_work_array (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_debugfs_terminate (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_destroy_multixri_pools (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_destroy_vport_work_array (struct lpfc_hba*,struct lpfc_vport**) ; 
 int /*<<< orphan*/  lpfc_disable_pci_dev (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_free_iocb_list (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_free_sysfs_attr (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_hba_free (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_io_free (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_nvme_destroy_localport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_nvmet_destroy_targetport (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_driver_resource_unset (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_hba_unset (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_pci_mem_unset (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_stop_hba_timers (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unset_driver_resource_phase2 (struct lpfc_hba*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_pci_remove_one_s4(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_vport **vports;
	struct lpfc_hba *phba = vport->phba;
	int i;

	/* Mark the device unloading flag */
	spin_lock_irq(&phba->hbalock);
	vport->load_flag |= FC_UNLOADING;
	spin_unlock_irq(&phba->hbalock);

	/* Free the HBA sysfs attributes */
	lpfc_free_sysfs_attr(vport);

	/* Release all the vports against this physical port */
	vports = lpfc_create_vport_work_array(phba);
	if (vports != NULL)
		for (i = 0; i <= phba->max_vports && vports[i] != NULL; i++) {
			if (vports[i]->port_type == LPFC_PHYSICAL_PORT)
				continue;
			fc_vport_terminate(vports[i]->fc_vport);
		}
	lpfc_destroy_vport_work_array(phba, vports);

	/* Remove FC host and then SCSI host with the physical port */
	fc_remove_host(shost);
	scsi_remove_host(shost);

	/* Perform ndlp cleanup on the physical port.  The nvme and nvmet
	 * localports are destroyed after to cleanup all transport memory.
	 */
	lpfc_cleanup(vport);
	lpfc_nvmet_destroy_targetport(phba);
	lpfc_nvme_destroy_localport(vport);

	/* De-allocate multi-XRI pools */
	if (phba->cfg_xri_rebalancing)
		lpfc_destroy_multixri_pools(phba);

	/*
	 * Bring down the SLI Layer. This step disables all interrupts,
	 * clears the rings, discards all mailbox commands, and resets
	 * the HBA FCoE function.
	 */
	lpfc_debugfs_terminate(vport);

	lpfc_stop_hba_timers(phba);
	spin_lock_irq(&phba->port_list_lock);
	list_del_init(&vport->listentry);
	spin_unlock_irq(&phba->port_list_lock);

	/* Perform scsi free before driver resource_unset since scsi
	 * buffers are released to their corresponding pools here.
	 */
	lpfc_io_free(phba);
	lpfc_free_iocb_list(phba);
	lpfc_sli4_hba_unset(phba);

	lpfc_unset_driver_resource_phase2(phba);
	lpfc_sli4_driver_resource_unset(phba);

	/* Unmap adapter Control and Doorbell registers */
	lpfc_sli4_pci_mem_unset(phba);

	/* Release PCI resources and disable device's PCI function */
	scsi_host_put(shost);
	lpfc_disable_pci_dev(phba);

	/* Finally, free the driver's device data structure */
	lpfc_hba_free(phba);

	return;
}