#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int fc_flag; scalar_t__ cfg_enable_fc4_type; scalar_t__ rcv_flogi_cnt; scalar_t__ fc_myDID; } ;
struct TYPE_21__ {int /*<<< orphan*/  logical_speed; } ;
struct TYPE_22__ {TYPE_7__ link_state; scalar_t__ conf_trunk; } ;
struct TYPE_19__ {scalar_t__ state; } ;
struct TYPE_18__ {scalar_t__ state; } ;
struct TYPE_17__ {scalar_t__ state; } ;
struct TYPE_16__ {scalar_t__ state; } ;
struct TYPE_20__ {TYPE_5__ link3; TYPE_4__ link2; TYPE_3__ link1; TYPE_2__ link0; } ;
struct TYPE_15__ {int fcf_flag; } ;
struct lpfc_hba {scalar_t__ link_state; int defer_flogi_acc_flag; int max_vports; scalar_t__ sli_rev; struct lpfc_vport* pport; int /*<<< orphan*/  mbox_mem_pool; scalar_t__ nvmet_support; TYPE_8__ sli4_hba; TYPE_6__ trunk_link; int /*<<< orphan*/  hbalock; TYPE_1__ fcf; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; } ;
struct TYPE_23__ {struct lpfc_vport* vport; void* mbox_cmpl; } ;
typedef  TYPE_9__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FCF_AVAILABLE ; 
 int FCF_SCAN_DONE ; 
 int FC_LBIT ; 
 int FC_PT2PT ; 
 int FC_PT2PT_PLOGI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LPFC_ENABLE_BOTH ; 
 scalar_t__ LPFC_ENABLE_NVME ; 
 scalar_t__ LPFC_LINK_DOWN ; 
 int /*<<< orphan*/  LPFC_LINK_SPEED_UNKNOWN ; 
 scalar_t__ LPFC_SLI_REV3 ; 
 int /*<<< orphan*/  LPFC_UNREG_ALL_DFLT_RPIS ; 
 scalar_t__ MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  lpfc_config_link (struct lpfc_hba*,TYPE_9__*) ; 
 struct lpfc_vport** lpfc_create_vport_work_array (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_destroy_vport_work_array (struct lpfc_hba*,struct lpfc_vport**) ; 
 int /*<<< orphan*/  lpfc_linkdown_port (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_nvme_update_localport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_nvmet_update_targetport (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_scsi_dev_block (struct lpfc_hba*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 void* lpfc_sli_def_mbox_cmpl ; 
 scalar_t__ lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_unreg_did (struct lpfc_hba*,int,int /*<<< orphan*/ ,TYPE_9__*) ; 
 TYPE_9__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
lpfc_linkdown(struct lpfc_hba *phba)
{
	struct lpfc_vport *vport = phba->pport;
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);
	struct lpfc_vport **vports;
	LPFC_MBOXQ_t          *mb;
	int i;

	if (phba->link_state == LPFC_LINK_DOWN)
		return 0;

	/* Block all SCSI stack I/Os */
	lpfc_scsi_dev_block(phba);

	phba->defer_flogi_acc_flag = false;

	spin_lock_irq(&phba->hbalock);
	phba->fcf.fcf_flag &= ~(FCF_AVAILABLE | FCF_SCAN_DONE);
	spin_unlock_irq(&phba->hbalock);
	if (phba->link_state > LPFC_LINK_DOWN) {
		phba->link_state = LPFC_LINK_DOWN;
		if (phba->sli4_hba.conf_trunk) {
			phba->trunk_link.link0.state = 0;
			phba->trunk_link.link1.state = 0;
			phba->trunk_link.link2.state = 0;
			phba->trunk_link.link3.state = 0;
			phba->sli4_hba.link_state.logical_speed =
						LPFC_LINK_SPEED_UNKNOWN;
		}
		spin_lock_irq(shost->host_lock);
		phba->pport->fc_flag &= ~FC_LBIT;
		spin_unlock_irq(shost->host_lock);
	}
	vports = lpfc_create_vport_work_array(phba);
	if (vports != NULL) {
		for (i = 0; i <= phba->max_vports && vports[i] != NULL; i++) {
			/* Issue a LINK DOWN event to all nodes */
			lpfc_linkdown_port(vports[i]);

			vports[i]->fc_myDID = 0;

			if ((vport->cfg_enable_fc4_type == LPFC_ENABLE_BOTH) ||
			    (vport->cfg_enable_fc4_type == LPFC_ENABLE_NVME)) {
				if (phba->nvmet_support)
					lpfc_nvmet_update_targetport(phba);
				else
					lpfc_nvme_update_localport(vports[i]);
			}
		}
	}
	lpfc_destroy_vport_work_array(phba, vports);

	/* Clean up any SLI3 firmware default rpi's */
	if (phba->sli_rev > LPFC_SLI_REV3)
		goto skip_unreg_did;

	mb = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (mb) {
		lpfc_unreg_did(phba, 0xffff, LPFC_UNREG_ALL_DFLT_RPIS, mb);
		mb->vport = vport;
		mb->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
		if (lpfc_sli_issue_mbox(phba, mb, MBX_NOWAIT)
		    == MBX_NOT_FINISHED) {
			mempool_free(mb, phba->mbox_mem_pool);
		}
	}

 skip_unreg_did:
	/* Setup myDID for link up if we are in pt2pt mode */
	if (phba->pport->fc_flag & FC_PT2PT) {
		mb = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
		if (mb) {
			lpfc_config_link(phba, mb);
			mb->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
			mb->vport = vport;
			if (lpfc_sli_issue_mbox(phba, mb, MBX_NOWAIT)
			    == MBX_NOT_FINISHED) {
				mempool_free(mb, phba->mbox_mem_pool);
			}
		}
		spin_lock_irq(shost->host_lock);
		phba->pport->fc_flag &= ~(FC_PT2PT | FC_PT2PT_PLOGI);
		phba->pport->rcv_flogi_cnt = 0;
		spin_unlock_irq(shost->host_lock);
	}
	return 0;
}