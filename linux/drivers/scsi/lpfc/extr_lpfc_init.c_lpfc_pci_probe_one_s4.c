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
typedef  scalar_t__ uint32_t ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct lpfc_vport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fcf_pri_list; } ;
struct lpfc_hba {scalar_t__ cfg_use_msi; scalar_t__ intr_type; int cfg_irq_chann; int cfg_enable_fc4_type; scalar_t__ nvmet_support; int cfg_nvmet_mrq; scalar_t__ cfg_request_firmware_upgrade; scalar_t__ intr_mode; struct lpfc_vport* pport; int /*<<< orphan*/  ModelDesc; int /*<<< orphan*/  ModelName; TYPE_1__ fcf; int /*<<< orphan*/  active_rrq_list; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT_FW_UPGRADE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int LPFC_ENABLE_NVME ; 
 scalar_t__ LPFC_INTR_ERROR ; 
 int /*<<< orphan*/  LPFC_PCI_DEV_OC ; 
 scalar_t__ MSIX ; 
 int lpfc_alloc_sysfs_attr (struct lpfc_vport*) ; 
 int lpfc_api_table_setup (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cpu_affinity_check (struct lpfc_hba*,int) ; 
 int lpfc_create_shost (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_create_static_vport (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_destroy_shost (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_disable_pci_dev (struct lpfc_hba*) ; 
 int lpfc_enable_pci_dev (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_free_sysfs_attr (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_get_hba_model_desc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lpfc_hba* lpfc_hba_alloc (struct pci_dev*) ; 
 int /*<<< orphan*/  lpfc_hba_free (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_log_intr_mode (struct lpfc_hba*,scalar_t__) ; 
 int lpfc_nvme_create_localport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_post_init_setup (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int lpfc_setup_driver_resource_phase2 (struct lpfc_hba*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_sli4_disable_intr (struct lpfc_hba*) ; 
 int lpfc_sli4_driver_resource_setup (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_driver_resource_unset (struct lpfc_hba*) ; 
 scalar_t__ lpfc_sli4_enable_intr (struct lpfc_hba*,scalar_t__) ; 
 scalar_t__ lpfc_sli4_hba_setup (struct lpfc_hba*) ; 
 int lpfc_sli4_pci_mem_setup (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_pci_mem_unset (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_ras_setup (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_request_firmware_update (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_stop_port (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unset_driver_resource_phase2 (struct lpfc_hba*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 

__attribute__((used)) static int
lpfc_pci_probe_one_s4(struct pci_dev *pdev, const struct pci_device_id *pid)
{
	struct lpfc_hba   *phba;
	struct lpfc_vport *vport = NULL;
	struct Scsi_Host  *shost = NULL;
	int error;
	uint32_t cfg_mode, intr_mode;

	/* Allocate memory for HBA structure */
	phba = lpfc_hba_alloc(pdev);
	if (!phba)
		return -ENOMEM;

	/* Perform generic PCI device enabling operation */
	error = lpfc_enable_pci_dev(phba);
	if (error)
		goto out_free_phba;

	/* Set up SLI API function jump table for PCI-device group-1 HBAs */
	error = lpfc_api_table_setup(phba, LPFC_PCI_DEV_OC);
	if (error)
		goto out_disable_pci_dev;

	/* Set up SLI-4 specific device PCI memory space */
	error = lpfc_sli4_pci_mem_setup(phba);
	if (error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1410 Failed to set up pci memory space.\n");
		goto out_disable_pci_dev;
	}

	/* Set up SLI-4 Specific device driver resources */
	error = lpfc_sli4_driver_resource_setup(phba);
	if (error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1412 Failed to set up driver resource.\n");
		goto out_unset_pci_mem_s4;
	}

	INIT_LIST_HEAD(&phba->active_rrq_list);
	INIT_LIST_HEAD(&phba->fcf.fcf_pri_list);

	/* Set up common device driver resources */
	error = lpfc_setup_driver_resource_phase2(phba);
	if (error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1414 Failed to set up driver resource.\n");
		goto out_unset_driver_resource_s4;
	}

	/* Get the default values for Model Name and Description */
	lpfc_get_hba_model_desc(phba, phba->ModelName, phba->ModelDesc);

	/* Now, trying to enable interrupt and bring up the device */
	cfg_mode = phba->cfg_use_msi;

	/* Put device to a known state before enabling interrupt */
	phba->pport = NULL;
	lpfc_stop_port(phba);

	/* Configure and enable interrupt */
	intr_mode = lpfc_sli4_enable_intr(phba, cfg_mode);
	if (intr_mode == LPFC_INTR_ERROR) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0426 Failed to enable interrupt.\n");
		error = -ENODEV;
		goto out_unset_driver_resource;
	}
	/* Default to single EQ for non-MSI-X */
	if (phba->intr_type != MSIX) {
		phba->cfg_irq_chann = 1;
		if (phba->cfg_enable_fc4_type & LPFC_ENABLE_NVME) {
			if (phba->nvmet_support)
				phba->cfg_nvmet_mrq = 1;
		}
	}
	lpfc_cpu_affinity_check(phba, phba->cfg_irq_chann);

	/* Create SCSI host to the physical port */
	error = lpfc_create_shost(phba);
	if (error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1415 Failed to create scsi host.\n");
		goto out_disable_intr;
	}
	vport = phba->pport;
	shost = lpfc_shost_from_vport(vport); /* save shost for error cleanup */

	/* Configure sysfs attributes */
	error = lpfc_alloc_sysfs_attr(vport);
	if (error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1416 Failed to allocate sysfs attr\n");
		goto out_destroy_shost;
	}

	/* Set up SLI-4 HBA */
	if (lpfc_sli4_hba_setup(phba)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1421 Failed to set up hba\n");
		error = -ENODEV;
		goto out_free_sysfs_attr;
	}

	/* Log the current active interrupt mode */
	phba->intr_mode = intr_mode;
	lpfc_log_intr_mode(phba, intr_mode);

	/* Perform post initialization setup */
	lpfc_post_init_setup(phba);

	/* NVME support in FW earlier in the driver load corrects the
	 * FC4 type making a check for nvme_support unnecessary.
	 */
	if (phba->nvmet_support == 0) {
		if (phba->cfg_enable_fc4_type & LPFC_ENABLE_NVME) {
			/* Create NVME binding with nvme_fc_transport. This
			 * ensures the vport is initialized.  If the localport
			 * create fails, it should not unload the driver to
			 * support field issues.
			 */
			error = lpfc_nvme_create_localport(vport);
			if (error) {
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
						"6004 NVME registration "
						"failed, error x%x\n",
						error);
			}
		}
	}

	/* check for firmware upgrade or downgrade */
	if (phba->cfg_request_firmware_upgrade)
		lpfc_sli4_request_firmware_update(phba, INT_FW_UPGRADE);

	/* Check if there are static vports to be created. */
	lpfc_create_static_vport(phba);

	/* Enable RAS FW log support */
	lpfc_sli4_ras_setup(phba);

	return 0;

out_free_sysfs_attr:
	lpfc_free_sysfs_attr(vport);
out_destroy_shost:
	lpfc_destroy_shost(phba);
out_disable_intr:
	lpfc_sli4_disable_intr(phba);
out_unset_driver_resource:
	lpfc_unset_driver_resource_phase2(phba);
out_unset_driver_resource_s4:
	lpfc_sli4_driver_resource_unset(phba);
out_unset_pci_mem_s4:
	lpfc_sli4_pci_mem_unset(phba);
out_disable_pci_dev:
	lpfc_disable_pci_dev(phba);
	if (shost)
		scsi_host_put(shost);
out_free_phba:
	lpfc_hba_free(phba);
	return error;
}