#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct TYPE_28__ {void* lsRjtRsnCodeExp; void* lsRjtRsnCode; } ;
struct TYPE_29__ {int /*<<< orphan*/  lsRjtError; TYPE_5__ b; } ;
struct ls_rjt {TYPE_6__ un; } ;
struct lpfc_vport {int load_flag; int fc_flag; int port_state; int rcv_flogi_cnt; int /*<<< orphan*/  fc_prevDID; int /*<<< orphan*/  fc_myDID; } ;
struct lpfc_sli_ring {int dummy; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; int nlp_flag; int /*<<< orphan*/  nlp_type; } ;
struct TYPE_24__ {int remoteID; int /*<<< orphan*/  parmRo; } ;
struct TYPE_20__ {int* ulpWord; TYPE_1__ rcvels; } ;
struct TYPE_26__ {int /*<<< orphan*/  acc_len; } ;
struct TYPE_27__ {TYPE_3__ rcvsli3; } ;
struct TYPE_23__ {int ulpStatus; int /*<<< orphan*/  ulpTimeout; TYPE_11__ un; TYPE_4__ unsli3; } ;
struct lpfc_iocbq {struct lpfc_nodelist* context1; TYPE_14__ iocb; struct lpfc_vport* vport; scalar_t__ context2; } ;
struct TYPE_21__ {int /*<<< orphan*/  elsRcvDrop; int /*<<< orphan*/  elsRcvECHO; int /*<<< orphan*/  elsRcvRRQ; int /*<<< orphan*/  elsRcvRTV; int /*<<< orphan*/  elsRcvRNID; int /*<<< orphan*/  elsRcvRPL; int /*<<< orphan*/  elsRcvRPS; int /*<<< orphan*/  elsRcvRLS; int /*<<< orphan*/  elsRcvLIRR; int /*<<< orphan*/  elsRcvPRLI; int /*<<< orphan*/  elsRcvFAN; int /*<<< orphan*/  elsRcvFARP; int /*<<< orphan*/  elsRcvFARPR; int /*<<< orphan*/  elsRcvPDISC; int /*<<< orphan*/  elsRcvADISC; int /*<<< orphan*/  elsRcvRSCN; int /*<<< orphan*/  elsRcvRDP; int /*<<< orphan*/  elsRcvLCB; int /*<<< orphan*/  elsRcvPRLO; int /*<<< orphan*/  elsRcvLOGO; int /*<<< orphan*/  elsRcvFLOGI; int /*<<< orphan*/  elsRcvPLOGI; int /*<<< orphan*/  elsRcvFrame; } ;
struct lpfc_hba {int sli3_options; TYPE_12__ fc_stat; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  cfg_link_speed; int /*<<< orphan*/  cfg_topology; TYPE_2__* pport; int /*<<< orphan*/  sli_rev; } ;
struct lpfc_dmabuf {int* virt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
typedef  int /*<<< orphan*/  stat ;
struct TYPE_30__ {scalar_t__ lipsr_AL_PA; } ;
struct TYPE_31__ {TYPE_7__ varInitLnk; } ;
struct TYPE_32__ {TYPE_8__ un; } ;
struct TYPE_25__ {int fc_flag; } ;
struct TYPE_19__ {TYPE_9__ mb; } ;
struct TYPE_22__ {struct lpfc_vport* vport; int /*<<< orphan*/  mbox_cmpl; TYPE_10__ u; } ;
typedef  TYPE_13__ LPFC_MBOXQ_t ;
typedef  TYPE_14__ IOCB_t ;

/* Variables and functions */
#define  ELS_CMD_ADISC 151 
#define  ELS_CMD_ECHO 150 
#define  ELS_CMD_FAN 149 
#define  ELS_CMD_FARP 148 
#define  ELS_CMD_FARPR 147 
#define  ELS_CMD_FLOGI 146 
#define  ELS_CMD_FPIN 145 
#define  ELS_CMD_LCB 144 
#define  ELS_CMD_LIRR 143 
#define  ELS_CMD_LOGO 142 
 int ELS_CMD_MASK ; 
#define  ELS_CMD_NVMEPRLI 141 
#define  ELS_CMD_PDISC 140 
#define  ELS_CMD_PLOGI 139 
#define  ELS_CMD_PRLI 138 
#define  ELS_CMD_PRLO 137 
#define  ELS_CMD_RDP 136 
#define  ELS_CMD_REC 135 
#define  ELS_CMD_RLS 134 
#define  ELS_CMD_RNID 133 
#define  ELS_CMD_RPL 132 
#define  ELS_CMD_RPS 131 
#define  ELS_CMD_RRQ 130 
#define  ELS_CMD_RSCN 129 
#define  ELS_CMD_RTV 128 
 int FC_DISC_DELAYED ; 
 int FC_FABRIC ; 
 int FC_PT2PT ; 
 int FC_PT2PT_PLOGI ; 
 int FC_UNLOADING ; 
 int Fabric_DID_MASK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int LPFC_DISC_AUTH ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_UNSOL ; 
 int LPFC_FABRIC_CFG_LINK ; 
 int LPFC_LOCAL_CFG_LINK ; 
 int LPFC_SLI3_HBQ_ENABLED ; 
 int /*<<< orphan*/  LPFC_SLI_REV4 ; 
 void* LSEXP_INVALID_OX_RX ; 
 void* LSEXP_NOTHING_MORE ; 
 void* LSRJT_CMD_UNSUPPORTED ; 
 void* LSRJT_LOGICAL_BSY ; 
 void* LSRJT_UNABLE_TPC ; 
 scalar_t__ MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_EVT_RCV_ADISC ; 
 int /*<<< orphan*/  NLP_EVT_RCV_LOGO ; 
 int /*<<< orphan*/  NLP_EVT_RCV_PDISC ; 
 int /*<<< orphan*/  NLP_EVT_RCV_PLOGI ; 
 int /*<<< orphan*/  NLP_EVT_RCV_PRLI ; 
 int /*<<< orphan*/  NLP_EVT_RCV_PRLO ; 
 int /*<<< orphan*/  NLP_FABRIC ; 
 int NLP_IN_DEV_LOSS ; 
 int /*<<< orphan*/  NLP_STE_NPR_NODE ; 
 scalar_t__ NLP_STE_UNUSED_NODE ; 
 int NLP_TARGET_REMOVE ; 
 int /*<<< orphan*/  fc_host_fpin_rcv (struct Scsi_Host*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  lpfc_disc_state_machine (struct lpfc_vport*,struct lpfc_nodelist*,struct lpfc_iocbq*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_els_chk_latt (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_echo (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_fan (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_farp (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_farpr (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_flogi (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_lcb (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_lirr (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_rdp (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_rls (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_rnid (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_rpl (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_rps (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_rrq (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_rscn (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rcv_rtv (struct lpfc_vport*,struct lpfc_iocbq*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_els_rsp_reject (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 struct lpfc_nodelist* lpfc_enable_node (struct lpfc_vport*,struct lpfc_nodelist*,scalar_t__) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int) ; 
 int /*<<< orphan*/  lpfc_init_link (struct lpfc_hba*,TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_linkdown (struct lpfc_hba*) ; 
 void* lpfc_nlp_get (struct lpfc_nodelist*) ; 
 struct lpfc_nodelist* lpfc_nlp_init (struct lpfc_vport*,int) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_set_state (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_plogi_confirm_nport (struct lpfc_hba*,int*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_post_buffer (struct lpfc_hba*,struct lpfc_sli_ring*,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  lpfc_send_els_event (struct lpfc_vport*,struct lpfc_nodelist*,int*) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_sli_def_mbox_cmpl ; 
 scalar_t__ lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_13__*,int /*<<< orphan*/ ) ; 
 TYPE_13__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ls_rjt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_els_unsol_buffer(struct lpfc_hba *phba, struct lpfc_sli_ring *pring,
		      struct lpfc_vport *vport, struct lpfc_iocbq *elsiocb)
{
	struct Scsi_Host  *shost;
	struct lpfc_nodelist *ndlp;
	struct ls_rjt stat;
	uint32_t *payload;
	uint32_t cmd, did, newnode;
	uint8_t rjt_exp, rjt_err = 0, init_link = 0;
	IOCB_t *icmd = &elsiocb->iocb;
	LPFC_MBOXQ_t *mbox;

	if (!vport || !(elsiocb->context2))
		goto dropit;

	newnode = 0;
	payload = ((struct lpfc_dmabuf *)elsiocb->context2)->virt;
	cmd = *payload;
	if ((phba->sli3_options & LPFC_SLI3_HBQ_ENABLED) == 0)
		lpfc_post_buffer(phba, pring, 1);

	did = icmd->un.rcvels.remoteID;
	if (icmd->ulpStatus) {
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV Unsol ELS:  status:x%x/x%x did:x%x",
			icmd->ulpStatus, icmd->un.ulpWord[4], did);
		goto dropit;
	}

	/* Check to see if link went down during discovery */
	if (lpfc_els_chk_latt(vport))
		goto dropit;

	/* Ignore traffic received during vport shutdown. */
	if (vport->load_flag & FC_UNLOADING)
		goto dropit;

	/* If NPort discovery is delayed drop incoming ELS */
	if ((vport->fc_flag & FC_DISC_DELAYED) &&
			(cmd != ELS_CMD_PLOGI))
		goto dropit;

	ndlp = lpfc_findnode_did(vport, did);
	if (!ndlp) {
		/* Cannot find existing Fabric ndlp, so allocate a new one */
		ndlp = lpfc_nlp_init(vport, did);
		if (!ndlp)
			goto dropit;
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
		newnode = 1;
		if ((did & Fabric_DID_MASK) == Fabric_DID_MASK)
			ndlp->nlp_type |= NLP_FABRIC;
	} else if (!NLP_CHK_NODE_ACT(ndlp)) {
		ndlp = lpfc_enable_node(vport, ndlp,
					NLP_STE_UNUSED_NODE);
		if (!ndlp)
			goto dropit;
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
		newnode = 1;
		if ((did & Fabric_DID_MASK) == Fabric_DID_MASK)
			ndlp->nlp_type |= NLP_FABRIC;
	} else if (ndlp->nlp_state == NLP_STE_UNUSED_NODE) {
		/* This is similar to the new node path */
		ndlp = lpfc_nlp_get(ndlp);
		if (!ndlp)
			goto dropit;
		lpfc_nlp_set_state(vport, ndlp, NLP_STE_NPR_NODE);
		newnode = 1;
	}

	phba->fc_stat.elsRcvFrame++;

	/*
	 * Do not process any unsolicited ELS commands
	 * if the ndlp is in DEV_LOSS
	 */
	shost = lpfc_shost_from_vport(vport);
	spin_lock_irq(shost->host_lock);
	if (ndlp->nlp_flag & NLP_IN_DEV_LOSS) {
		spin_unlock_irq(shost->host_lock);
		goto dropit;
	}
	spin_unlock_irq(shost->host_lock);

	elsiocb->context1 = lpfc_nlp_get(ndlp);
	elsiocb->vport = vport;

	if ((cmd & ELS_CMD_MASK) == ELS_CMD_RSCN) {
		cmd &= ELS_CMD_MASK;
	}
	/* ELS command <elsCmd> received from NPORT <did> */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			 "0112 ELS command x%x received from NPORT x%x "
			 "Data: x%x x%x x%x x%x\n",
			cmd, did, vport->port_state, vport->fc_flag,
			vport->fc_myDID, vport->fc_prevDID);

	/* reject till our FLOGI completes or PLOGI assigned DID via PT2PT */
	if ((vport->port_state < LPFC_FABRIC_CFG_LINK) &&
	    (cmd != ELS_CMD_FLOGI) &&
	    !((cmd == ELS_CMD_PLOGI) && (vport->fc_flag & FC_PT2PT))) {
		rjt_err = LSRJT_LOGICAL_BSY;
		rjt_exp = LSEXP_NOTHING_MORE;
		goto lsrjt;
	}

	switch (cmd) {
	case ELS_CMD_PLOGI:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV PLOGI:       did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvPLOGI++;
		ndlp = lpfc_plogi_confirm_nport(phba, payload, ndlp);
		if (phba->sli_rev == LPFC_SLI_REV4 &&
		    (phba->pport->fc_flag & FC_PT2PT)) {
			vport->fc_prevDID = vport->fc_myDID;
			/* Our DID needs to be updated before registering
			 * the vfi. This is done in lpfc_rcv_plogi but
			 * that is called after the reg_vfi.
			 */
			vport->fc_myDID = elsiocb->iocb.un.rcvels.parmRo;
			lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
					 "3312 Remote port assigned DID x%x "
					 "%x\n", vport->fc_myDID,
					 vport->fc_prevDID);
		}

		lpfc_send_els_event(vport, ndlp, payload);

		/* If Nport discovery is delayed, reject PLOGIs */
		if (vport->fc_flag & FC_DISC_DELAYED) {
			rjt_err = LSRJT_UNABLE_TPC;
			rjt_exp = LSEXP_NOTHING_MORE;
			break;
		}

		if (vport->port_state < LPFC_DISC_AUTH) {
			if (!(phba->pport->fc_flag & FC_PT2PT) ||
				(phba->pport->fc_flag & FC_PT2PT_PLOGI)) {
				rjt_err = LSRJT_UNABLE_TPC;
				rjt_exp = LSEXP_NOTHING_MORE;
				break;
			}
		}

		spin_lock_irq(shost->host_lock);
		ndlp->nlp_flag &= ~NLP_TARGET_REMOVE;
		spin_unlock_irq(shost->host_lock);

		lpfc_disc_state_machine(vport, ndlp, elsiocb,
					NLP_EVT_RCV_PLOGI);

		break;
	case ELS_CMD_FLOGI:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV FLOGI:       did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvFLOGI++;

		/* If the driver believes fabric discovery is done and is ready,
		 * bounce the link.  There is some descrepancy.
		 */
		if (vport->port_state >= LPFC_LOCAL_CFG_LINK &&
		    vport->fc_flag & FC_PT2PT &&
		    vport->rcv_flogi_cnt >= 1) {
			rjt_err = LSRJT_LOGICAL_BSY;
			rjt_exp = LSEXP_NOTHING_MORE;
			init_link++;
			goto lsrjt;
		}

		lpfc_els_rcv_flogi(vport, elsiocb, ndlp);
		if (newnode)
			lpfc_nlp_put(ndlp);
		break;
	case ELS_CMD_LOGO:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV LOGO:        did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvLOGO++;
		lpfc_send_els_event(vport, ndlp, payload);
		if (vport->port_state < LPFC_DISC_AUTH) {
			rjt_err = LSRJT_UNABLE_TPC;
			rjt_exp = LSEXP_NOTHING_MORE;
			break;
		}
		lpfc_disc_state_machine(vport, ndlp, elsiocb, NLP_EVT_RCV_LOGO);
		break;
	case ELS_CMD_PRLO:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV PRLO:        did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvPRLO++;
		lpfc_send_els_event(vport, ndlp, payload);
		if (vport->port_state < LPFC_DISC_AUTH) {
			rjt_err = LSRJT_UNABLE_TPC;
			rjt_exp = LSEXP_NOTHING_MORE;
			break;
		}
		lpfc_disc_state_machine(vport, ndlp, elsiocb, NLP_EVT_RCV_PRLO);
		break;
	case ELS_CMD_LCB:
		phba->fc_stat.elsRcvLCB++;
		lpfc_els_rcv_lcb(vport, elsiocb, ndlp);
		break;
	case ELS_CMD_RDP:
		phba->fc_stat.elsRcvRDP++;
		lpfc_els_rcv_rdp(vport, elsiocb, ndlp);
		break;
	case ELS_CMD_RSCN:
		phba->fc_stat.elsRcvRSCN++;
		lpfc_els_rcv_rscn(vport, elsiocb, ndlp);
		if (newnode)
			lpfc_nlp_put(ndlp);
		break;
	case ELS_CMD_ADISC:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV ADISC:       did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		lpfc_send_els_event(vport, ndlp, payload);
		phba->fc_stat.elsRcvADISC++;
		if (vport->port_state < LPFC_DISC_AUTH) {
			rjt_err = LSRJT_UNABLE_TPC;
			rjt_exp = LSEXP_NOTHING_MORE;
			break;
		}
		lpfc_disc_state_machine(vport, ndlp, elsiocb,
					NLP_EVT_RCV_ADISC);
		break;
	case ELS_CMD_PDISC:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV PDISC:       did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvPDISC++;
		if (vport->port_state < LPFC_DISC_AUTH) {
			rjt_err = LSRJT_UNABLE_TPC;
			rjt_exp = LSEXP_NOTHING_MORE;
			break;
		}
		lpfc_disc_state_machine(vport, ndlp, elsiocb,
					NLP_EVT_RCV_PDISC);
		break;
	case ELS_CMD_FARPR:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV FARPR:       did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvFARPR++;
		lpfc_els_rcv_farpr(vport, elsiocb, ndlp);
		break;
	case ELS_CMD_FARP:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV FARP:        did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvFARP++;
		lpfc_els_rcv_farp(vport, elsiocb, ndlp);
		break;
	case ELS_CMD_FAN:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV FAN:         did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvFAN++;
		lpfc_els_rcv_fan(vport, elsiocb, ndlp);
		break;
	case ELS_CMD_PRLI:
	case ELS_CMD_NVMEPRLI:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV PRLI:        did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvPRLI++;
		if ((vport->port_state < LPFC_DISC_AUTH) &&
		    (vport->fc_flag & FC_FABRIC)) {
			rjt_err = LSRJT_UNABLE_TPC;
			rjt_exp = LSEXP_NOTHING_MORE;
			break;
		}
		lpfc_disc_state_machine(vport, ndlp, elsiocb, NLP_EVT_RCV_PRLI);
		break;
	case ELS_CMD_LIRR:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV LIRR:        did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvLIRR++;
		lpfc_els_rcv_lirr(vport, elsiocb, ndlp);
		if (newnode)
			lpfc_nlp_put(ndlp);
		break;
	case ELS_CMD_RLS:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV RLS:         did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvRLS++;
		lpfc_els_rcv_rls(vport, elsiocb, ndlp);
		if (newnode)
			lpfc_nlp_put(ndlp);
		break;
	case ELS_CMD_RPS:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV RPS:         did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvRPS++;
		lpfc_els_rcv_rps(vport, elsiocb, ndlp);
		if (newnode)
			lpfc_nlp_put(ndlp);
		break;
	case ELS_CMD_RPL:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV RPL:         did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvRPL++;
		lpfc_els_rcv_rpl(vport, elsiocb, ndlp);
		if (newnode)
			lpfc_nlp_put(ndlp);
		break;
	case ELS_CMD_RNID:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV RNID:        did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvRNID++;
		lpfc_els_rcv_rnid(vport, elsiocb, ndlp);
		if (newnode)
			lpfc_nlp_put(ndlp);
		break;
	case ELS_CMD_RTV:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV RTV:        did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);
		phba->fc_stat.elsRcvRTV++;
		lpfc_els_rcv_rtv(vport, elsiocb, ndlp);
		if (newnode)
			lpfc_nlp_put(ndlp);
		break;
	case ELS_CMD_RRQ:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV RRQ:         did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvRRQ++;
		lpfc_els_rcv_rrq(vport, elsiocb, ndlp);
		if (newnode)
			lpfc_nlp_put(ndlp);
		break;
	case ELS_CMD_ECHO:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV ECHO:        did:x%x/ste:x%x flg:x%x",
			did, vport->port_state, ndlp->nlp_flag);

		phba->fc_stat.elsRcvECHO++;
		lpfc_els_rcv_echo(vport, elsiocb, ndlp);
		if (newnode)
			lpfc_nlp_put(ndlp);
		break;
	case ELS_CMD_REC:
		/* receive this due to exchange closed */
		rjt_err = LSRJT_UNABLE_TPC;
		rjt_exp = LSEXP_INVALID_OX_RX;
		break;
	case ELS_CMD_FPIN:
		/*
		 * Received FPIN from fabric - pass it to the
		 * transport FPIN handler.
		 */
		fc_host_fpin_rcv(shost, elsiocb->iocb.unsli3.rcvsli3.acc_len,
				(char *)payload);
		break;
	default:
		lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_UNSOL,
			"RCV ELS cmd:     cmd:x%x did:x%x/ste:x%x",
			cmd, did, vport->port_state);

		/* Unsupported ELS command, reject */
		rjt_err = LSRJT_CMD_UNSUPPORTED;
		rjt_exp = LSEXP_NOTHING_MORE;

		/* Unknown ELS command <elsCmd> received from NPORT <did> */
		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
				 "0115 Unknown ELS command x%x "
				 "received from NPORT x%x\n", cmd, did);
		if (newnode)
			lpfc_nlp_put(ndlp);
		break;
	}

lsrjt:
	/* check if need to LS_RJT received ELS cmd */
	if (rjt_err) {
		memset(&stat, 0, sizeof(stat));
		stat.un.b.lsRjtRsnCode = rjt_err;
		stat.un.b.lsRjtRsnCodeExp = rjt_exp;
		lpfc_els_rsp_reject(vport, stat.un.lsRjtError, elsiocb, ndlp,
			NULL);
	}

	lpfc_nlp_put(elsiocb->context1);
	elsiocb->context1 = NULL;

	/* Special case.  Driver received an unsolicited command that
	 * unsupportable given the driver's current state.  Reset the
	 * link and start over.
	 */
	if (init_link) {
		mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
		if (!mbox)
			return;
		lpfc_linkdown(phba);
		lpfc_init_link(phba, mbox,
			       phba->cfg_topology,
			       phba->cfg_link_speed);
		mbox->u.mb.un.varInitLnk.lipsr_AL_PA = 0;
		mbox->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
		mbox->vport = vport;
		if (lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT) ==
		    MBX_NOT_FINISHED)
			mempool_free(mbox, phba->mbox_mem_pool);
	}

	return;

dropit:
	if (vport && !(vport->load_flag & FC_UNLOADING))
		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
			"0111 Dropping received ELS cmd "
			"Data: x%x x%x x%x\n",
			icmd->ulpStatus, icmd->un.ulpWord[4], icmd->ulpTimeout);
	phba->fc_stat.elsRcvDrop++;
}