#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct serv_parm {int dummy; } ;
struct lpfc_vport {int /*<<< orphan*/  vpi; int /*<<< orphan*/  port_state; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_rpi; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; struct serv_parm fc_fabparam; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; } ;
struct TYPE_7__ {scalar_t__ ctx_buf; int /*<<< orphan*/  ctx_ndlp; struct lpfc_vport* vport; int /*<<< orphan*/  mbox_cmpl; } ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int /*<<< orphan*/  Fabric_DID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_FABRIC_CFG_LINK ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 int /*<<< orphan*/  lpfc_config_link (struct lpfc_hba*,TYPE_1__*) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_fabric_reg_login ; 
 int /*<<< orphan*/  lpfc_nlp_get (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int lpfc_reg_rpi (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli_def_mbox_cmpl ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
lpfc_issue_fabric_reglogin(struct lpfc_vport *vport)
{
	struct lpfc_hba  *phba = vport->phba;
	LPFC_MBOXQ_t *mbox;
	struct lpfc_dmabuf *mp;
	struct lpfc_nodelist *ndlp;
	struct serv_parm *sp;
	int rc;
	int err = 0;

	sp = &phba->fc_fabparam;
	ndlp = lpfc_findnode_did(vport, Fabric_DID);
	if (!ndlp || !NLP_CHK_NODE_ACT(ndlp)) {
		err = 1;
		goto fail;
	}

	mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mbox) {
		err = 2;
		goto fail;
	}

	vport->port_state = LPFC_FABRIC_CFG_LINK;
	lpfc_config_link(phba, mbox);
	mbox->mbox_cmpl = lpfc_sli_def_mbox_cmpl;
	mbox->vport = vport;

	rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
	if (rc == MBX_NOT_FINISHED) {
		err = 3;
		goto fail_free_mbox;
	}

	mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mbox) {
		err = 4;
		goto fail;
	}
	rc = lpfc_reg_rpi(phba, vport->vpi, Fabric_DID, (uint8_t *)sp, mbox,
			  ndlp->nlp_rpi);
	if (rc) {
		err = 5;
		goto fail_free_mbox;
	}

	mbox->mbox_cmpl = lpfc_mbx_cmpl_fabric_reg_login;
	mbox->vport = vport;
	/* increment the reference count on ndlp to hold reference
	 * for the callback routine.
	 */
	mbox->ctx_ndlp = lpfc_nlp_get(ndlp);

	rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
	if (rc == MBX_NOT_FINISHED) {
		err = 6;
		goto fail_issue_reg_login;
	}

	return 0;

fail_issue_reg_login:
	/* decrement the reference count on ndlp just incremented
	 * for the failed mbox command.
	 */
	lpfc_nlp_put(ndlp);
	mp = (struct lpfc_dmabuf *)mbox->ctx_buf;
	lpfc_mbuf_free(phba, mp->virt, mp->phys);
	kfree(mp);
fail_free_mbox:
	mempool_free(mbox, phba->mbox_mem_pool);

fail:
	lpfc_vport_set_state(vport, FC_VPORT_FAILED);
	lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
		"0249 Cannot issue Register Fabric login: Err %d\n", err);
	return -ENXIO;
}