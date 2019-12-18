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
struct lpfc_vport {int fc_flag; scalar_t__ port_type; scalar_t__ vpi; } ;
struct TYPE_3__ {int /*<<< orphan*/  vpi_used; } ;
struct TYPE_4__ {TYPE_1__ max_cfg_param; } ;
struct lpfc_hba {scalar_t__ sli_rev; int cfg_enable_fc4_type; int max_vports; int sli3_options; scalar_t__ cfg_xri_rebalancing; struct lpfc_vport* pport; int /*<<< orphan*/  nvmet_support; int /*<<< orphan*/  hbalock; TYPE_2__ sli4_hba; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; } ;

/* Variables and functions */
 int FC_OFFLINE_MODE ; 
 int FC_VPORT_NEEDS_INIT_VPI ; 
 int FC_VPORT_NEEDS_REG_VPI ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int LPFC_ENABLE_NVME ; 
 int /*<<< orphan*/  LPFC_MBX_WAIT ; 
 scalar_t__ LPFC_PHYSICAL_PORT ; 
 int LPFC_SLI3_NPIV_ENABLED ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  lpfc_block_mgmt_io (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_create_multixri_pools (struct lpfc_hba*) ; 
 struct lpfc_vport** lpfc_create_vport_work_array (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_destroy_vport_work_array (struct lpfc_hba*,struct lpfc_vport**) ; 
 int lpfc_nvme_create_localport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 scalar_t__ lpfc_sli4_hba_setup (struct lpfc_hba*) ; 
 scalar_t__ lpfc_sli_hba_setup (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_queue_init (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unblock_mgmt_io (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
lpfc_online(struct lpfc_hba *phba)
{
	struct lpfc_vport *vport;
	struct lpfc_vport **vports;
	int i, error = 0;
	bool vpis_cleared = false;

	if (!phba)
		return 0;
	vport = phba->pport;

	if (!(vport->fc_flag & FC_OFFLINE_MODE))
		return 0;

	lpfc_printf_log(phba, KERN_WARNING, LOG_INIT,
			"0458 Bring Adapter online\n");

	lpfc_block_mgmt_io(phba, LPFC_MBX_WAIT);

	if (phba->sli_rev == LPFC_SLI_REV4) {
		if (lpfc_sli4_hba_setup(phba)) { /* Initialize SLI4 HBA */
			lpfc_unblock_mgmt_io(phba);
			return 1;
		}
		spin_lock_irq(&phba->hbalock);
		if (!phba->sli4_hba.max_cfg_param.vpi_used)
			vpis_cleared = true;
		spin_unlock_irq(&phba->hbalock);

		/* Reestablish the local initiator port.
		 * The offline process destroyed the previous lport.
		 */
		if (phba->cfg_enable_fc4_type & LPFC_ENABLE_NVME &&
				!phba->nvmet_support) {
			error = lpfc_nvme_create_localport(phba->pport);
			if (error)
				lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
					"6132 NVME restore reg failed "
					"on nvmei error x%x\n", error);
		}
	} else {
		lpfc_sli_queue_init(phba);
		if (lpfc_sli_hba_setup(phba)) {	/* Initialize SLI2/SLI3 HBA */
			lpfc_unblock_mgmt_io(phba);
			return 1;
		}
	}

	vports = lpfc_create_vport_work_array(phba);
	if (vports != NULL) {
		for (i = 0; i <= phba->max_vports && vports[i] != NULL; i++) {
			struct Scsi_Host *shost;
			shost = lpfc_shost_from_vport(vports[i]);
			spin_lock_irq(shost->host_lock);
			vports[i]->fc_flag &= ~FC_OFFLINE_MODE;
			if (phba->sli3_options & LPFC_SLI3_NPIV_ENABLED)
				vports[i]->fc_flag |= FC_VPORT_NEEDS_REG_VPI;
			if (phba->sli_rev == LPFC_SLI_REV4) {
				vports[i]->fc_flag |= FC_VPORT_NEEDS_INIT_VPI;
				if ((vpis_cleared) &&
				    (vports[i]->port_type !=
					LPFC_PHYSICAL_PORT))
					vports[i]->vpi = 0;
			}
			spin_unlock_irq(shost->host_lock);
		}
	}
	lpfc_destroy_vport_work_array(phba, vports);

	if (phba->cfg_xri_rebalancing)
		lpfc_create_multixri_pools(phba);

	lpfc_unblock_mgmt_io(phba);
	return 0;
}