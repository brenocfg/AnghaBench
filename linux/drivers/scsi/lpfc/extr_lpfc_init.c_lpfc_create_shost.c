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
struct lpfc_vport {int /*<<< orphan*/  fdmi_port_mask; int /*<<< orphan*/  fdmi_hba_mask; int /*<<< orphan*/  load_flag; } ;
struct lpfc_hba {scalar_t__ cfg_fdmi_on; scalar_t__ cfg_enable_SmartSAN; TYPE_1__* pcidev; int /*<<< orphan*/  cfg_enable_fc4_type; int /*<<< orphan*/ * targetport; int /*<<< orphan*/ * txrdy_payload_pool; scalar_t__ nvmet_support; struct lpfc_vport* pport; int /*<<< orphan*/  brd_no; int /*<<< orphan*/  sdev_cnt; int /*<<< orphan*/  fc_arbtov; int /*<<< orphan*/  fc_altov; int /*<<< orphan*/  fc_ratov; int /*<<< orphan*/  fc_edtov; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FC_ALLOW_FDMI ; 
 int /*<<< orphan*/  FF_DEF_ALTOV ; 
 int /*<<< orphan*/  FF_DEF_ARBTOV ; 
 int /*<<< orphan*/  FF_DEF_EDTOV ; 
 int /*<<< orphan*/  FF_DEF_RATOV ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LOG_INIT ; 
 int LOG_NVME_DISC ; 
 int /*<<< orphan*/  LPFC_ENABLE_NVME ; 
 int /*<<< orphan*/  LPFC_FDMI2_HBA_ATTR ; 
 int /*<<< orphan*/  LPFC_FDMI2_PORT_ATTR ; 
 int /*<<< orphan*/  LPFC_FDMI2_SMART_ATTR ; 
 scalar_t__ LPFC_FDMI_SUPPORT ; 
 int /*<<< orphan*/  TXRDY_PAYLOAD_LEN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_pool_create (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct lpfc_vport* lpfc_create_port (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_debugfs_initialize (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int,char*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  pci_set_drvdata (TYPE_1__*,struct Scsi_Host*) ; 

__attribute__((used)) static int
lpfc_create_shost(struct lpfc_hba *phba)
{
	struct lpfc_vport *vport;
	struct Scsi_Host  *shost;

	/* Initialize HBA FC structure */
	phba->fc_edtov = FF_DEF_EDTOV;
	phba->fc_ratov = FF_DEF_RATOV;
	phba->fc_altov = FF_DEF_ALTOV;
	phba->fc_arbtov = FF_DEF_ARBTOV;

	atomic_set(&phba->sdev_cnt, 0);
	vport = lpfc_create_port(phba, phba->brd_no, &phba->pcidev->dev);
	if (!vport)
		return -ENODEV;

	shost = lpfc_shost_from_vport(vport);
	phba->pport = vport;

	if (phba->nvmet_support) {
		/* Only 1 vport (pport) will support NVME target */
		if (phba->txrdy_payload_pool == NULL) {
			phba->txrdy_payload_pool = dma_pool_create(
				"txrdy_pool", &phba->pcidev->dev,
				TXRDY_PAYLOAD_LEN, 16, 0);
			if (phba->txrdy_payload_pool) {
				phba->targetport = NULL;
				phba->cfg_enable_fc4_type = LPFC_ENABLE_NVME;
				lpfc_printf_log(phba, KERN_INFO,
						LOG_INIT | LOG_NVME_DISC,
						"6076 NVME Target Found\n");
			}
		}
	}

	lpfc_debugfs_initialize(vport);
	/* Put reference to SCSI host to driver's device private data */
	pci_set_drvdata(phba->pcidev, shost);

	/*
	 * At this point we are fully registered with PSA. In addition,
	 * any initial discovery should be completed.
	 */
	vport->load_flag |= FC_ALLOW_FDMI;
	if (phba->cfg_enable_SmartSAN ||
	    (phba->cfg_fdmi_on == LPFC_FDMI_SUPPORT)) {

		/* Setup appropriate attribute masks */
		vport->fdmi_hba_mask = LPFC_FDMI2_HBA_ATTR;
		if (phba->cfg_enable_SmartSAN)
			vport->fdmi_port_mask = LPFC_FDMI2_SMART_ATTR;
		else
			vport->fdmi_port_mask = LPFC_FDMI2_PORT_ATTR;
	}
	return 0;
}