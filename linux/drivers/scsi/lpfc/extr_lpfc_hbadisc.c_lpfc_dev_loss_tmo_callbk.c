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
struct lpfc_work_evt {int /*<<< orphan*/  evt_listp; int /*<<< orphan*/  evt; scalar_t__ evt_arg1; } ;
struct lpfc_vport {int load_flag; struct lpfc_hba* phba; } ;
struct lpfc_rport_data {struct lpfc_nodelist* pnode; } ;
struct TYPE_3__ {int /*<<< orphan*/  wwn; } ;
struct TYPE_4__ {TYPE_1__ u; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; int /*<<< orphan*/  nlp_flag; struct lpfc_work_evt dev_loss_evt; TYPE_2__ nlp_portname; int /*<<< orphan*/ * rport; int /*<<< orphan*/  nlp_DID; struct lpfc_vport* vport; int /*<<< orphan*/  nlp_sid; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; int /*<<< orphan*/  work_list; } ;
struct fc_rport {scalar_t__ port_name; int /*<<< orphan*/  dev; struct lpfc_rport_data* dd_data; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; } ;

/* Variables and functions */
 int FC_UNLOADING ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NODE ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_RPORT ; 
 int /*<<< orphan*/  LPFC_EVT_DEV_LOSS ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_IN_DEV_LOSS ; 
 scalar_t__ NLP_STE_MAPPED_NODE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_nlp_get (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ wwn_to_u64 (int /*<<< orphan*/ ) ; 

void
lpfc_dev_loss_tmo_callbk(struct fc_rport *rport)
{
	struct lpfc_rport_data *rdata;
	struct lpfc_nodelist * ndlp;
	struct lpfc_vport *vport;
	struct Scsi_Host *shost;
	struct lpfc_hba   *phba;
	struct lpfc_work_evt *evtp;
	int  put_node;
	int  put_rport;
	unsigned long iflags;

	rdata = rport->dd_data;
	ndlp = rdata->pnode;
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp))
		return;

	vport = ndlp->vport;
	phba  = vport->phba;

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_RPORT,
		"rport devlosscb: sid:x%x did:x%x flg:x%x",
		ndlp->nlp_sid, ndlp->nlp_DID, ndlp->nlp_flag);

	lpfc_printf_vlog(ndlp->vport, KERN_INFO, LOG_NODE,
			 "3181 dev_loss_callbk x%06x, rport x%px flg x%x\n",
			 ndlp->nlp_DID, ndlp->rport, ndlp->nlp_flag);

	/* Don't defer this if we are in the process of deleting the vport
	 * or unloading the driver. The unload will cleanup the node
	 * appropriately we just need to cleanup the ndlp rport info here.
	 */
	if (vport->load_flag & FC_UNLOADING) {
		put_node = rdata->pnode != NULL;
		put_rport = ndlp->rport != NULL;
		rdata->pnode = NULL;
		ndlp->rport = NULL;
		if (put_node)
			lpfc_nlp_put(ndlp);
		if (put_rport)
			put_device(&rport->dev);
		return;
	}

	if (ndlp->nlp_state == NLP_STE_MAPPED_NODE)
		return;

	if (rport->port_name != wwn_to_u64(ndlp->nlp_portname.u.wwn))
		lpfc_printf_vlog(vport, KERN_ERR, LOG_NODE,
				"6789 rport name %llx != node port name %llx",
				rport->port_name,
				wwn_to_u64(ndlp->nlp_portname.u.wwn));

	evtp = &ndlp->dev_loss_evt;

	if (!list_empty(&evtp->evt_listp)) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_NODE,
				"6790 rport name %llx dev_loss_evt pending",
				rport->port_name);
		return;
	}

	shost = lpfc_shost_from_vport(vport);
	spin_lock_irqsave(shost->host_lock, iflags);
	ndlp->nlp_flag |= NLP_IN_DEV_LOSS;
	spin_unlock_irqrestore(shost->host_lock, iflags);

	/* We need to hold the node by incrementing the reference
	 * count until this queued work is done
	 */
	evtp->evt_arg1  = lpfc_nlp_get(ndlp);

	spin_lock_irqsave(&phba->hbalock, iflags);
	if (evtp->evt_arg1) {
		evtp->evt = LPFC_EVT_DEV_LOSS;
		list_add_tail(&evtp->evt_listp, &phba->work_list);
		lpfc_worker_wake_up(phba);
	}
	spin_unlock_irqrestore(&phba->hbalock, iflags);

	return;
}