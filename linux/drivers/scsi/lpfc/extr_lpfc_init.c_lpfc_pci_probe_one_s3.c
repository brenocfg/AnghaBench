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
typedef  int /*<<< orphan*/  uint32_t ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct lpfc_vport {int dummy; } ;
struct TYPE_3__ {scalar_t__ sli_intr; } ;
struct TYPE_4__ {TYPE_1__ slistat; } ;
struct lpfc_hba {int /*<<< orphan*/  intr_mode; TYPE_2__ sli; int /*<<< orphan*/  cfg_use_msi; struct lpfc_vport* pport; int /*<<< orphan*/  ModelDesc; int /*<<< orphan*/  ModelName; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_INTR_ERROR ; 
 int /*<<< orphan*/  LPFC_IOCB_LIST_CNT ; 
 scalar_t__ LPFC_MSIX_VECTORS ; 
 int /*<<< orphan*/  LPFC_PCI_DEV_LP ; 
 int lpfc_alloc_sysfs_attr (struct lpfc_vport*) ; 
 int lpfc_api_table_setup (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int lpfc_create_shost (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_create_static_vport (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_destroy_shost (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_disable_pci_dev (struct lpfc_hba*) ; 
 int lpfc_enable_pci_dev (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_free_iocb_list (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_free_sysfs_attr (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_get_hba_model_desc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lpfc_hba* lpfc_hba_alloc (struct pci_dev*) ; 
 int /*<<< orphan*/  lpfc_hba_free (struct lpfc_hba*) ; 
 int lpfc_init_iocb_list (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_log_intr_mode (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_post_init_setup (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int lpfc_setup_driver_resource_phase2 (struct lpfc_hba*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_sli_disable_intr (struct lpfc_hba*) ; 
 int lpfc_sli_driver_resource_setup (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_driver_resource_unset (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_enable_intr (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_sli_hba_setup (struct lpfc_hba*) ; 
 int lpfc_sli_pci_mem_setup (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_pci_mem_unset (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_stop_port (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unset_driver_resource_phase2 (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unset_hba (struct lpfc_hba*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 

__attribute__((used)) static int
lpfc_pci_probe_one_s3(struct pci_dev *pdev, const struct pci_device_id *pid)
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

	/* Set up SLI API function jump table for PCI-device group-0 HBAs */
	error = lpfc_api_table_setup(phba, LPFC_PCI_DEV_LP);
	if (error)
		goto out_disable_pci_dev;

	/* Set up SLI-3 specific device PCI memory space */
	error = lpfc_sli_pci_mem_setup(phba);
	if (error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1402 Failed to set up pci memory space.\n");
		goto out_disable_pci_dev;
	}

	/* Set up SLI-3 specific device driver resources */
	error = lpfc_sli_driver_resource_setup(phba);
	if (error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1404 Failed to set up driver resource.\n");
		goto out_unset_pci_mem_s3;
	}

	/* Initialize and populate the iocb list per host */

	error = lpfc_init_iocb_list(phba, LPFC_IOCB_LIST_CNT);
	if (error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1405 Failed to initialize iocb list.\n");
		goto out_unset_driver_resource_s3;
	}

	/* Set up common device driver resources */
	error = lpfc_setup_driver_resource_phase2(phba);
	if (error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1406 Failed to set up driver resource.\n");
		goto out_free_iocb_list;
	}

	/* Get the default values for Model Name and Description */
	lpfc_get_hba_model_desc(phba, phba->ModelName, phba->ModelDesc);

	/* Create SCSI host to the physical port */
	error = lpfc_create_shost(phba);
	if (error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1407 Failed to create scsi host.\n");
		goto out_unset_driver_resource;
	}

	/* Configure sysfs attributes */
	vport = phba->pport;
	error = lpfc_alloc_sysfs_attr(vport);
	if (error) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"1476 Failed to allocate sysfs attr\n");
		goto out_destroy_shost;
	}

	shost = lpfc_shost_from_vport(vport); /* save shost for error cleanup */
	/* Now, trying to enable interrupt and bring up the device */
	cfg_mode = phba->cfg_use_msi;
	while (true) {
		/* Put device to a known state before enabling interrupt */
		lpfc_stop_port(phba);
		/* Configure and enable interrupt */
		intr_mode = lpfc_sli_enable_intr(phba, cfg_mode);
		if (intr_mode == LPFC_INTR_ERROR) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"0431 Failed to enable interrupt.\n");
			error = -ENODEV;
			goto out_free_sysfs_attr;
		}
		/* SLI-3 HBA setup */
		if (lpfc_sli_hba_setup(phba)) {
			lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"1477 Failed to set up hba\n");
			error = -ENODEV;
			goto out_remove_device;
		}

		/* Wait 50ms for the interrupts of previous mailbox commands */
		msleep(50);
		/* Check active interrupts on message signaled interrupts */
		if (intr_mode == 0 ||
		    phba->sli.slistat.sli_intr > LPFC_MSIX_VECTORS) {
			/* Log the current active interrupt mode */
			phba->intr_mode = intr_mode;
			lpfc_log_intr_mode(phba, intr_mode);
			break;
		} else {
			lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
					"0447 Configure interrupt mode (%d) "
					"failed active interrupt test.\n",
					intr_mode);
			/* Disable the current interrupt mode */
			lpfc_sli_disable_intr(phba);
			/* Try next level of interrupt mode */
			cfg_mode = --intr_mode;
		}
	}

	/* Perform post initialization setup */
	lpfc_post_init_setup(phba);

	/* Check if there are static vports to be created. */
	lpfc_create_static_vport(phba);

	return 0;

out_remove_device:
	lpfc_unset_hba(phba);
out_free_sysfs_attr:
	lpfc_free_sysfs_attr(vport);
out_destroy_shost:
	lpfc_destroy_shost(phba);
out_unset_driver_resource:
	lpfc_unset_driver_resource_phase2(phba);
out_free_iocb_list:
	lpfc_free_iocb_list(phba);
out_unset_driver_resource_s3:
	lpfc_sli_driver_resource_unset(phba);
out_unset_pci_mem_s3:
	lpfc_sli_pci_mem_unset(phba);
out_disable_pci_dev:
	lpfc_disable_pci_dev(phba);
	if (shost)
		scsi_host_put(shost);
out_free_phba:
	lpfc_hba_free(phba);
	return error;
}