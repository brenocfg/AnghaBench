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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct lpfc_vport {scalar_t__ fc_myDID; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  nlp_flag; } ;
struct lpfc_node_rrq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ulpContext; } ;
struct lpfc_iocbq {TYPE_1__ iocb; int /*<<< orphan*/  iotag; scalar_t__ context2; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct RRQ {scalar_t__ rrq_exchg; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_ELS_RSP ; 
 scalar_t__ be32_to_cpu (scalar_t__) ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct RRQ*) ; 
 int /*<<< orphan*/  lpfc_clr_rrq_active (struct lpfc_hba*,scalar_t__,struct lpfc_node_rrq*) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct lpfc_node_rrq* lpfc_get_active_rrq (struct lpfc_vport*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrq_did ; 
 int /*<<< orphan*/  rrq_oxid ; 
 int /*<<< orphan*/  rrq_rxid ; 

__attribute__((used)) static void
lpfc_els_clear_rrq(struct lpfc_vport *vport,
		   struct lpfc_iocbq *iocb, struct lpfc_nodelist *ndlp)
{
	struct lpfc_hba  *phba = vport->phba;
	uint8_t *pcmd;
	struct RRQ *rrq;
	uint16_t rxid;
	uint16_t xri;
	struct lpfc_node_rrq *prrq;


	pcmd = (uint8_t *) (((struct lpfc_dmabuf *) iocb->context2)->virt);
	pcmd += sizeof(uint32_t);
	rrq = (struct RRQ *)pcmd;
	rrq->rrq_exchg = be32_to_cpu(rrq->rrq_exchg);
	rxid = bf_get(rrq_rxid, rrq);

	lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
			"2883 Clear RRQ for SID:x%x OXID:x%x RXID:x%x"
			" x%x x%x\n",
			be32_to_cpu(bf_get(rrq_did, rrq)),
			bf_get(rrq_oxid, rrq),
			rxid,
			iocb->iotag, iocb->iocb.ulpContext);

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_ELS_RSP,
		"Clear RRQ:  did:x%x flg:x%x exchg:x%.08x",
		ndlp->nlp_DID, ndlp->nlp_flag, rrq->rrq_exchg);
	if (vport->fc_myDID == be32_to_cpu(bf_get(rrq_did, rrq)))
		xri = bf_get(rrq_oxid, rrq);
	else
		xri = rxid;
	prrq = lpfc_get_active_rrq(vport, xri, ndlp->nlp_DID);
	if (prrq)
		lpfc_clr_rrq_active(phba, xri, prrq);
	return;
}