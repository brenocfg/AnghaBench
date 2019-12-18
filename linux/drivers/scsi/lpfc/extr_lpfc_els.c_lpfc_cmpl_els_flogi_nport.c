#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct serv_parm {int /*<<< orphan*/  nodeName; int /*<<< orphan*/  portName; } ;
struct lpfc_vport {int fc_flag; int /*<<< orphan*/  fc_myDID; int /*<<< orphan*/  fc_portname; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_flag; int /*<<< orphan*/  nlp_nodename; int /*<<< orphan*/  nlp_portname; } ;
struct lpfc_name {int dummy; } ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  mbox_mem_pool; scalar_t__ fc_topology_changed; int /*<<< orphan*/  sli3_options; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_6__ {struct lpfc_vport* vport; int /*<<< orphan*/  mbox_cmpl; } ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int ENXIO ; 
 int FC_FABRIC ; 
 int FC_PT2PT ; 
 int FC_PT2PT_PLOGI ; 
 int FC_PUBLIC_LOOP ; 
 int FC_VFI_REGISTERED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LPFC_SLI3_NPIV_ENABLED ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_NPR_2B_DISC ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 int /*<<< orphan*/  NLP_STE_UNUSED_NODE ; 
 int /*<<< orphan*/  PT2PT_LocalID ; 
 int /*<<< orphan*/  PT2PT_RemoteID ; 
 int /*<<< orphan*/  lpfc_config_link (struct lpfc_hba*,TYPE_1__*) ; 
 int /*<<< orphan*/  lpfc_disc_start (struct lpfc_vport*) ; 
 struct lpfc_nodelist* lpfc_enable_node (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_local_config_link ; 
 struct lpfc_nodelist* lpfc_nlp_init (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_unregister_fcf_prep (struct lpfc_hba*) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_cmpl_els_flogi_nport(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			  struct serv_parm *sp)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba  *phba = vport->phba;
	LPFC_MBOXQ_t *mbox;
	int rc;

	spin_lock_irq(shost->host_lock);
	vport->fc_flag &= ~(FC_FABRIC | FC_PUBLIC_LOOP);
	vport->fc_flag |= FC_PT2PT;
	spin_unlock_irq(shost->host_lock);

	/* If we are pt2pt with another NPort, force NPIV off! */
	phba->sli3_options &= ~LPFC_SLI3_NPIV_ENABLED;

	/* If physical FC port changed, unreg VFI and ALL VPIs / RPIs */
	if ((phba->sli_rev == LPFC_SLI_REV4) && phba->fc_topology_changed) {
		lpfc_unregister_fcf_prep(phba);

		spin_lock_irq(shost->host_lock);
		vport->fc_flag &= ~FC_VFI_REGISTERED;
		spin_unlock_irq(shost->host_lock);
		phba->fc_topology_changed = 0;
	}

	rc = memcmp(&vport->fc_portname, &sp->portName,
		    sizeof(vport->fc_portname));

	if (rc >= 0) {
		/* This side will initiate the PLOGI */
		spin_lock_irq(shost->host_lock);
		vport->fc_flag |= FC_PT2PT_PLOGI;
		spin_unlock_irq(shost->host_lock);

		/*
		 * N_Port ID cannot be 0, set our Id to LocalID
		 * the other side will be RemoteID.
		 */

		/* not equal */
		if (rc)
			vport->fc_myDID = PT2PT_LocalID;

		/* Decrement ndlp reference count indicating that ndlp can be
		 * safely released when other references to it are done.
		 */
		lpfc_nlp_put(ndlp);

		ndlp = lpfc_findnode_did(vport, PT2PT_RemoteID);
		if (!ndlp) {
			/*
			 * Cannot find existing Fabric ndlp, so allocate a
			 * new one
			 */
			ndlp = lpfc_nlp_init(vport, PT2PT_RemoteID);
			if (!ndlp)
				goto fail;
		} else if (!NLP_CHK_NODE_ACT(ndlp)) {
			ndlp = lpfc_enable_node(vport, ndlp,
						NLP_STE_UNUSED_NODE);
			if(!ndlp)
				goto fail;
		}

		memcpy(&ndlp->nlp_portname, &sp->portName,
		       sizeof(struct lpfc_name));
		memcpy(&ndlp->nlp_nodename, &sp->nodeName,
		       sizeof(struct lpfc_name));
		/* Set state will put ndlp onto node list if not already done */
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag |= NLP_NPR_2B_DISC;
		spin_unlock_irq(shost->host_lock);

		mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
		if (!mbox)
			goto fail;

		lpfc_config_link(phba, mbox);

		mbox->mbox_cmpl = lpfc_mbx_cmpl_local_config_link;
		mbox->vport = vport;
		rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
		if (rc == MBX_NOT_FINISHED) {
			mempool_free(mbox, phba->mbox_mem_pool);
			goto fail;
		}
	} else {
		/* This side will wait for the PLOGI, decrement ndlp reference
		 * count indicating that ndlp can be released when other
		 * references to it are done.
		 */
		lpfc_nlp_put(ndlp);

		/* Start discovery - this should just do CLEAR_LA */
		lpfc_disc_start(vport);
	}

	return 0;
fail:
	return -ENXIO;
}