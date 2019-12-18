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
struct serv_parm {int dummy; } ;
struct lpfc_vport {int fc_flag; int /*<<< orphan*/  port_state; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int dummy; } ;
struct lpfc_hba {scalar_t__ sli_rev; int link_flag; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  fc_fabparam; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; scalar_t__ virt; } ;
struct TYPE_6__ {struct lpfc_dmabuf* ctx_buf; struct lpfc_vport* vport; int /*<<< orphan*/  mbox_cmpl; } ;
typedef  TYPE_1__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int FC_FABRIC ; 
 int FC_PT2PT ; 
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int /*<<< orphan*/  Fabric_DID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_FABRIC_CFG_LINK ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int LS_LOOPBACK_MODE ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int /*<<< orphan*/  MEM_PRI ; 
 int /*<<< orphan*/  NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  kfree (struct lpfc_dmabuf*) ; 
 struct lpfc_dmabuf* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 scalar_t__ lpfc_mbuf_alloc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_mbuf_free (struct lpfc_hba*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_mbx_cmpl_reg_vfi ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lpfc_reg_vfi (TYPE_1__*,struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
lpfc_issue_reg_vfi(struct lpfc_vport *vport)
{
	struct lpfc_hba  *phba = vport->phba;
	LPFC_MBOXQ_t *mboxq = NULL;
	struct lpfc_nodelist *ndlp;
	struct lpfc_dmabuf *dmabuf = NULL;
	int rc = 0;

	/* move forward in case of SLI4 FC port loopback test and pt2pt mode */
	if ((phba->sli_rev == LPFC_SLI_REV4) &&
	    !(phba->link_flag & LS_LOOPBACK_MODE) &&
	    !(vport->fc_flag & FC_PT2PT)) {
		ndlp = lpfc_findnode_did(vport, Fabric_DID);
		if (!ndlp || !NLP_CHK_NODE_ACT(ndlp)) {
			rc = -ENODEV;
			goto fail;
		}
	}

	mboxq = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mboxq) {
		rc = -ENOMEM;
		goto fail;
	}

	/* Supply CSP's only if we are fabric connect or pt-to-pt connect */
	if ((vport->fc_flag & FC_FABRIC) || (vport->fc_flag & FC_PT2PT)) {
		dmabuf = kzalloc(sizeof(struct lpfc_dmabuf), GFP_KERNEL);
		if (!dmabuf) {
			rc = -ENOMEM;
			goto fail;
		}
		dmabuf->virt = lpfc_mbuf_alloc(phba, MEM_PRI, &dmabuf->phys);
		if (!dmabuf->virt) {
			rc = -ENOMEM;
			goto fail;
		}
		memcpy(dmabuf->virt, &phba->fc_fabparam,
		       sizeof(struct serv_parm));
	}

	vport->port_state = LPFC_FABRIC_CFG_LINK;
	if (dmabuf)
		lpfc_reg_vfi(mboxq, vport, dmabuf->phys);
	else
		lpfc_reg_vfi(mboxq, vport, 0);

	mboxq->mbox_cmpl = lpfc_mbx_cmpl_reg_vfi;
	mboxq->vport = vport;
	mboxq->ctx_buf = dmabuf;
	rc = lpfc_sli_issue_mbox(phba, mboxq, MBX_NOWAIT);
	if (rc == MBX_NOT_FINISHED) {
		rc = -ENXIO;
		goto fail;
	}
	return 0;

fail:
	if (mboxq)
		mempool_free(mboxq, phba->mbox_mem_pool);
	if (dmabuf) {
		if (dmabuf->virt)
			lpfc_mbuf_free(phba, dmabuf->virt, dmabuf->phys);
		kfree(dmabuf);
	}

	lpfc_vport_set_state(vport, FC_VPORT_FAILED);
	lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
		"0289 Issue Register VFI failed: Err %d\n", rc);
	return rc;
}