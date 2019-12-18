#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_17__ {scalar_t__ vendorUnique; int /*<<< orphan*/  lsRjtRsnCodeExp; int /*<<< orphan*/  lsRjtRsnCode; scalar_t__ lsRjtRsvd0; } ;
struct TYPE_18__ {int /*<<< orphan*/  lsRjtError; TYPE_5__ b; } ;
struct ls_rjt {TYPE_6__ un; } ;
struct lpfc_vport {int /*<<< orphan*/  fc_portname; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; } ;
struct lpfc_name {int dummy; } ;
struct TYPE_14__ {int ox_id; } ;
struct TYPE_15__ {TYPE_2__ rcvsli3; } ;
struct TYPE_16__ {int ulpContext; TYPE_3__ unsli3; } ;
struct lpfc_iocbq {TYPE_4__ iocb; scalar_t__ context2; } ;
struct lpfc_hba {int /*<<< orphan*/  mbox_mem_pool; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct TYPE_20__ {int /*<<< orphan*/  mbox_cmpl; struct lpfc_vport* vport; int /*<<< orphan*/  ctx_ndlp; void* ctx_buf; } ;
struct TYPE_13__ {int /*<<< orphan*/  portName; int /*<<< orphan*/  portNum; } ;
struct TYPE_19__ {TYPE_1__ un; } ;
typedef  TYPE_7__ RPS ;
typedef  TYPE_8__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LSEXP_CANT_GIVE_DATA ; 
 int /*<<< orphan*/  LSRJT_UNABLE_TPC ; 
 scalar_t__ MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 scalar_t__ NLP_STE_MAPPED_NODE ; 
 scalar_t__ NLP_STE_UNMAPPED_NODE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  lpfc_els_rsp_reject (struct lpfc_vport*,int /*<<< orphan*/ ,struct lpfc_iocbq*,struct lpfc_nodelist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_els_rsp_rps_acc ; 
 int /*<<< orphan*/  lpfc_nlp_get (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_read_lnk_stat (struct lpfc_hba*,TYPE_8__*) ; 
 scalar_t__ lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_8__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int
lpfc_els_rcv_rps(struct lpfc_vport *vport, struct lpfc_iocbq *cmdiocb,
		 struct lpfc_nodelist *ndlp)
{
	struct lpfc_hba *phba = vport->phba;
	uint32_t *lp;
	uint8_t flag;
	LPFC_MBOXQ_t *mbox;
	struct lpfc_dmabuf *pcmd;
	RPS *rps;
	struct ls_rjt stat;

	if ((ndlp->nlp_state != NLP_STE_UNMAPPED_NODE) &&
	    (ndlp->nlp_state != NLP_STE_MAPPED_NODE))
		/* reject the unsolicited RPS request and done with it */
		goto reject_out;

	pcmd = (struct lpfc_dmabuf *) cmdiocb->context2;
	lp = (uint32_t *) pcmd->virt;
	flag = (be32_to_cpu(*lp++) & 0xf);
	rps = (RPS *) lp;

	if ((flag == 0) ||
	    ((flag == 1) && (be32_to_cpu(rps->un.portNum) == 0)) ||
	    ((flag == 2) && (memcmp(&rps->un.portName, &vport->fc_portname,
				    sizeof(struct lpfc_name)) == 0))) {

		printk("Fix me....\n");
		dump_stack();
		mbox = mempool_alloc(phba->mbox_mem_pool, GFP_ATOMIC);
		if (mbox) {
			lpfc_read_lnk_stat(phba, mbox);
			mbox->ctx_buf = (void *)((unsigned long)
				((cmdiocb->iocb.unsli3.rcvsli3.ox_id << 16) |
				cmdiocb->iocb.ulpContext)); /* rx_id */
			mbox->ctx_ndlp = lpfc_nlp_get(ndlp);
			mbox->vport = vport;
			mbox->mbox_cmpl = lpfc_els_rsp_rps_acc;
			if (lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT)
				!= MBX_NOT_FINISHED)
				/* Mbox completion will send ELS Response */
				return 0;
			/* Decrement reference count used for the failed mbox
			 * command.
			 */
			lpfc_nlp_put(ndlp);
			mempool_free(mbox, phba->mbox_mem_pool);
		}
	}

reject_out:
	/* issue rejection response */
	stat.un.b.lsRjtRsvd0 = 0;
	stat.un.b.lsRjtRsnCode = LSRJT_UNABLE_TPC;
	stat.un.b.lsRjtRsnCodeExp = LSEXP_CANT_GIVE_DATA;
	stat.un.b.vendorUnique = 0;
	lpfc_els_rsp_reject(vport, stat.un.lsRjtError, cmdiocb, ndlp, NULL);
	return 0;
}