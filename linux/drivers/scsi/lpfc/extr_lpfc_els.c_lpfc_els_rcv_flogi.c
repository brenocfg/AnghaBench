#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct serv_parm {int /*<<< orphan*/  portName; } ;
struct lpfc_vport {int fc_flag; void* fc_myDID; void* port_state; int /*<<< orphan*/  rcv_flogi_cnt; int /*<<< orphan*/  fc_portname; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_name {int dummy; } ;
struct TYPE_22__ {int /*<<< orphan*/  ox_id; } ;
struct TYPE_23__ {TYPE_7__ rcvsli3; } ;
struct TYPE_16__ {void* remoteID; } ;
struct TYPE_17__ {TYPE_1__ elsreq64; } ;
struct TYPE_15__ {TYPE_8__ unsli3; int /*<<< orphan*/  ulpContext; TYPE_2__ un; } ;
struct lpfc_iocbq {TYPE_10__ iocb; scalar_t__ context2; } ;
struct lpfc_hba {scalar_t__ fc_topology; scalar_t__ sli_rev; int hba_flag; int defer_flogi_acc_flag; int /*<<< orphan*/  defer_flogi_acc_ox_id; int /*<<< orphan*/  defer_flogi_acc_rx_id; int /*<<< orphan*/  fc_fabparam; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  cfg_link_speed; int /*<<< orphan*/  cfg_topology; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_18__ {scalar_t__ lipsr_AL_PA; } ;
struct TYPE_19__ {TYPE_3__ varInitLnk; } ;
struct TYPE_20__ {TYPE_4__ un; } ;
struct TYPE_21__ {TYPE_5__ mb; } ;
struct TYPE_24__ {struct lpfc_vport* vport; int /*<<< orphan*/  mbox_cmpl; TYPE_6__ u; } ;
typedef  TYPE_9__ LPFC_MBOXQ_t ;
typedef  TYPE_10__ IOCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS3 ; 
 int /*<<< orphan*/  ELS_CMD_FLOGI ; 
 int FC_FABRIC ; 
 int FC_PT2PT ; 
 int FC_PT2PT_PLOGI ; 
 int FC_PUBLIC_LOOP ; 
 void* Fabric_DID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HBA_FLOGI_ISSUED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 void* PT2PT_LocalID ; 
 void* PT2PT_RemoteID ; 
 int /*<<< orphan*/  lpfc_check_sparm (struct lpfc_vport*,struct lpfc_nodelist*,struct serv_parm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpfc_els_abort_flogi (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_els_rsp_acc (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_init_link (struct lpfc_hba*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_linkdown (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*,void*,...) ; 
 int /*<<< orphan*/  lpfc_set_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_set_loopback_flag (struct lpfc_hba*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_sli_def_mbox_cmpl ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct serv_parm*,int) ; 
 TYPE_9__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_els_rcv_flogi(struct lpfc_vport *vport, struct lpfc_iocbq *cmdiocb,
		   struct lpfc_nodelist *ndlp)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_hba  *phba = vport->phba;
	struct lpfc_dmabuf *pcmd = (struct lpfc_dmabuf *) cmdiocb->context2;
	uint32_t *lp = (uint32_t *) pcmd->virt;
	IOCB_t *icmd = &cmdiocb->iocb;
	struct serv_parm *sp;
	LPFC_MBOXQ_t *mbox;
	uint32_t cmd, did;
	int rc;
	uint32_t fc_flag = 0;
	uint32_t port_state = 0;

	cmd = *lp++;
	sp = (struct serv_parm *) lp;

	/* FLOGI received */

	lpfc_set_disctmo(vport);

	if (phba->fc_topology == LPFC_TOPOLOGY_LOOP) {
		/* We should never receive a FLOGI in loop mode, ignore it */
		did = icmd->un.elsreq64.remoteID;

		/* An FLOGI ELS command <elsCmd> was received from DID <did> in
		   Loop Mode */
		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
				 "0113 An FLOGI ELS command x%x was "
				 "received from DID x%x in Loop Mode\n",
				 cmd, did);
		return 1;
	}

	(void) lpfc_check_sparm(vport, ndlp, sp, CLASS3, 1);

	/*
	 * If our portname is greater than the remote portname,
	 * then we initiate Nport login.
	 */

	rc = memcmp(&vport->fc_portname, &sp->portName,
		    sizeof(struct lpfc_name));

	if (!rc) {
		if (phba->sli_rev < LPFC_SLI_REV4) {
			mbox = mempool_alloc(phba->mbox_mem_pool,
					     GFP_KERNEL);
			if (!mbox)
				return 1;
			lpfc_linkdown(phba);
			lpfc_init_link(phba, mbox,
				       phba->cfg_topology,
				       phba->cfg_link_speed);
			mbox->u.mb.un.varInitLnk.lipsr_AL_PA = 0;
			mbox->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
			mbox->vport = vport;
			rc = lpfc_sli_issue_mbox(phba, mbox,
						 MBX_NOWAIT);
			lpfc_set_loopback_flag(phba);
			if (rc == MBX_NOT_FINISHED)
				mempool_free(mbox, phba->mbox_mem_pool);
			return 1;
		}

		/* abort the flogi coming back to ourselves
		 * due to external loopback on the port.
		 */
		lpfc_els_abort_flogi(phba);
		return 0;

	} else if (rc > 0) {	/* greater than */
		spin_lock_irq(shost->host_lock);
		vport->fc_flag |= FC_PT2PT_PLOGI;
		spin_unlock_irq(shost->host_lock);

		/* If we have the high WWPN we can assign our own
		 * myDID; otherwise, we have to WAIT for a PLOGI
		 * from the remote NPort to find out what it
		 * will be.
		 */
		vport->fc_myDID = PT2PT_LocalID;
	} else {
		vport->fc_myDID = PT2PT_RemoteID;
	}

	/*
	 * The vport state should go to LPFC_FLOGI only
	 * AFTER we issue a FLOGI, not receive one.
	 */
	spin_lock_irq(shost->host_lock);
	fc_flag = vport->fc_flag;
	port_state = vport->port_state;
	vport->fc_flag |= FC_PT2PT;
	vport->fc_flag &= ~(FC_FABRIC | FC_PUBLIC_LOOP);

	/* Acking an unsol FLOGI.  Count 1 for link bounce
	 * work-around.
	 */
	vport->rcv_flogi_cnt++;
	spin_unlock_irq(shost->host_lock);
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "3311 Rcv Flogi PS x%x new PS x%x "
			 "fc_flag x%x new fc_flag x%x\n",
			 port_state, vport->port_state,
			 fc_flag, vport->fc_flag);

	/*
	 * We temporarily set fc_myDID to make it look like we are
	 * a Fabric. This is done just so we end up with the right
	 * did / sid on the FLOGI ACC rsp.
	 */
	did = vport->fc_myDID;
	vport->fc_myDID = Fabric_DID;

	memcpy(&phba->fc_fabparam, sp, sizeof(struct serv_parm));

	/* Defer ACC response until AFTER we issue a FLOGI */
	if (!(phba->hba_flag & HBA_FLOGI_ISSUED)) {
		phba->defer_flogi_acc_rx_id = cmdiocb->iocb.ulpContext;
		phba->defer_flogi_acc_ox_id =
					cmdiocb->iocb.unsli3.rcvsli3.ox_id;

		vport->fc_myDID = did;

		lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
				 "3344 Deferring FLOGI ACC: rx_id: x%x,"
				 " ox_id: x%x, hba_flag x%x\n",
				 phba->defer_flogi_acc_rx_id,
				 phba->defer_flogi_acc_ox_id, phba->hba_flag);

		phba->defer_flogi_acc_flag = true;

		return 0;
	}

	/* Send back ACC */
	lpfc_els_rsp_acc(vport, ELS_CMD_FLOGI, cmdiocb, ndlp, NULL);

	/* Now lets put fc_myDID back to what its supposed to be */
	vport->fc_myDID = did;

	return 0;
}