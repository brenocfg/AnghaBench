#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct lpfc_vport {scalar_t__ port_type; int /*<<< orphan*/  listentry; int /*<<< orphan*/  fc_vport; int /*<<< orphan*/  load_flag; struct lpfc_hba* phba; } ;
struct TYPE_4__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct TYPE_3__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct lpfc_hba {int max_vports; int /*<<< orphan*/  slim_memmap_p; int /*<<< orphan*/  ctrl_regs_memmap_p; TYPE_2__ slim2p; TYPE_1__ hbqslimp; scalar_t__ cfg_sriov_nr_virtfn; int /*<<< orphan*/  port_list_lock; int /*<<< orphan*/  vpi_ids; int /*<<< orphan*/  vpi_bmask; int /*<<< orphan*/  worker_thread; int /*<<< orphan*/  hbalock; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_UNLOADING ; 
 scalar_t__ LPFC_PHYSICAL_PORT ; 
 int /*<<< orphan*/  SLI2_SLIM_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  fc_vport_terminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_cleanup (struct lpfc_vport*) ; 
 struct lpfc_vport** lpfc_create_vport_work_array (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_debugfs_terminate (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_destroy_vport_work_array (struct lpfc_hba*,struct lpfc_vport**) ; 
 int /*<<< orphan*/  lpfc_free_iocb_list (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_free_sysfs_attr (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_hba_free (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_mem_free_all (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_scsi_free (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_brdrestart (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_disable_intr (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_hba_down (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_hbq_size () ; 
 int /*<<< orphan*/  lpfc_stop_hba_timers (struct lpfc_hba*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_pci_remove_one_s3(struct pci_dev *pdev)
{
	struct Scsi_Host  *shost = pci_get_drvdata(pdev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_vport **vports;
	struct lpfc_hba   *phba = vport->phba;
	int i;

	spin_lock_irq(&phba->hbalock);
	vport->load_flag |= FC_UNLOADING;
	spin_unlock_irq(&phba->hbalock);

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

	lpfc_cleanup(vport);

	/*
	 * Bring down the SLI Layer. This step disable all interrupts,
	 * clears the rings, discards all mailbox commands, and resets
	 * the HBA.
	 */

	/* HBA interrupt will be disabled after this call */
	lpfc_sli_hba_down(phba);
	/* Stop kthread signal shall trigger work_done one more time */
	kthread_stop(phba->worker_thread);
	/* Final cleanup of txcmplq and reset the HBA */
	lpfc_sli_brdrestart(phba);

	kfree(phba->vpi_bmask);
	kfree(phba->vpi_ids);

	lpfc_stop_hba_timers(phba);
	spin_lock_irq(&phba->port_list_lock);
	list_del_init(&vport->listentry);
	spin_unlock_irq(&phba->port_list_lock);

	lpfc_debugfs_terminate(vport);

	/* Disable SR-IOV if enabled */
	if (phba->cfg_sriov_nr_virtfn)
		pci_disable_sriov(pdev);

	/* Disable interrupt */
	lpfc_sli_disable_intr(phba);

	scsi_host_put(shost);

	/*
	 * Call scsi_free before mem_free since scsi bufs are released to their
	 * corresponding pools here.
	 */
	lpfc_scsi_free(phba);
	lpfc_free_iocb_list(phba);

	lpfc_mem_free_all(phba);

	dma_free_coherent(&pdev->dev, lpfc_sli_hbq_size(),
			  phba->hbqslimp.virt, phba->hbqslimp.phys);

	/* Free resources associated with SLI2 interface */
	dma_free_coherent(&pdev->dev, SLI2_SLIM_SIZE,
			  phba->slim2p.virt, phba->slim2p.phys);

	/* unmap adapter SLIM and Control Registers */
	iounmap(phba->ctrl_regs_memmap_p);
	iounmap(phba->slim_memmap_p);

	lpfc_hba_free(phba);

	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
}