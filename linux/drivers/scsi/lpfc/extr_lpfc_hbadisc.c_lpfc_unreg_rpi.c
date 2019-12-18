#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct lpfc_vport {int load_flag; int fc_flag; int /*<<< orphan*/  vpi; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {int nlp_flag; size_t nlp_rpi; int nlp_DID; int /*<<< orphan*/  kref; int /*<<< orphan*/  nlp_defer_did; } ;
struct TYPE_7__ {size_t* rpi_ids; int /*<<< orphan*/  sli_intf; } ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  mbox_mem_pool; TYPE_1__ sli4_hba; } ;
struct TYPE_8__ {void* mbox_cmpl; struct lpfc_nodelist* ctx_ndlp; struct lpfc_vport* vport; } ;
typedef  TYPE_2__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int FC_OFFLINE_MODE ; 
 int FC_UNLOADING ; 
 int Fabric_DID_MASK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  LOG_SLI ; 
 scalar_t__ LPFC_SLI_INTF_IF_TYPE_2 ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int MBX_NOT_FINISHED ; 
 int /*<<< orphan*/  MBX_NOWAIT ; 
 int NLP_ISSUE_LOGO ; 
 int NLP_LOGO_ACC ; 
 int NLP_NPR_ADISC ; 
 int NLP_REG_LOGIN_SEND ; 
 int NLP_RPI_REGISTERED ; 
 int NLP_UNREG_INP ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kref_read (int /*<<< orphan*/ *) ; 
 struct lpfc_nodelist* lpfc_nlp_get (struct lpfc_nodelist*) ; 
 void* lpfc_nlp_logo_unreg ; 
 int /*<<< orphan*/  lpfc_no_rpi (struct lpfc_hba*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int,int,...) ; 
 void* lpfc_sli4_unreg_rpi_cmpl_clr ; 
 void* lpfc_sli_def_mbox_cmpl ; 
 int /*<<< orphan*/  lpfc_sli_intf_if_type ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_unreg_login (struct lpfc_hba*,int /*<<< orphan*/ ,size_t,TYPE_2__*) ; 
 TYPE_2__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
lpfc_unreg_rpi(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp)
{
	struct lpfc_hba *phba = vport->phba;
	LPFC_MBOXQ_t    *mbox;
	int rc, acc_plogi = 1;
	uint16_t rpi;

	if (ndlp->nlp_flag & NLP_RPI_REGISTERED ||
	    ndlp->nlp_flag & NLP_REG_LOGIN_SEND) {
		if (ndlp->nlp_flag & NLP_REG_LOGIN_SEND)
			lpfc_printf_vlog(vport, KERN_INFO, LOG_SLI,
					 "3366 RPI x%x needs to be "
					 "unregistered nlp_flag x%x "
					 "did x%x\n",
					 ndlp->nlp_rpi, ndlp->nlp_flag,
					 ndlp->nlp_DID);

		/* If there is already an UNREG in progress for this ndlp,
		 * no need to queue up another one.
		 */
		if (ndlp->nlp_flag & NLP_UNREG_INP) {
			lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
					 "1436 unreg_rpi SKIP UNREG x%x on "
					 "NPort x%x deferred x%x  flg x%x "
					 "Data: x%px\n",
					 ndlp->nlp_rpi, ndlp->nlp_DID,
					 ndlp->nlp_defer_did,
					 ndlp->nlp_flag, ndlp);
			goto out;
		}

		mbox = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
		if (mbox) {
			/* SLI4 ports require the physical rpi value. */
			rpi = ndlp->nlp_rpi;
			if (phba->sli_rev == LPFC_SLI_REV4)
				rpi = phba->sli4_hba.rpi_ids[ndlp->nlp_rpi];

			lpfc_unreg_login(phba, vport->vpi, rpi, mbox);
			mbox->vport = vport;
			if (ndlp->nlp_flag & NLP_ISSUE_LOGO) {
				mbox->ctx_ndlp = ndlp;
				mbox->mbox_cmpl = lpfc_nlp_logo_unreg;
			} else {
				if (phba->sli_rev == LPFC_SLI_REV4 &&
				    (!(vport->load_flag & FC_UNLOADING)) &&
				    (bf_get(lpfc_sli_intf_if_type,
				     &phba->sli4_hba.sli_intf) >=
				      LPFC_SLI_INTF_IF_TYPE_2) &&
				    (kref_read(&ndlp->kref) > 0)) {
					mbox->ctx_ndlp = lpfc_nlp_get(ndlp);
					mbox->mbox_cmpl =
						lpfc_sli4_unreg_rpi_cmpl_clr;
					/*
					 * accept PLOGIs after unreg_rpi_cmpl
					 */
					acc_plogi = 0;
				} else if (vport->load_flag & FC_UNLOADING) {
					mbox->ctx_ndlp = NULL;
					mbox->mbox_cmpl =
						lpfc_sli_def_mbox_cmpl;
				} else {
					mbox->ctx_ndlp = ndlp;
					mbox->mbox_cmpl =
						lpfc_sli_def_mbox_cmpl;
				}
			}
			if (((ndlp->nlp_DID & Fabric_DID_MASK) !=
			    Fabric_DID_MASK) &&
			    (!(vport->fc_flag & FC_OFFLINE_MODE)))
				ndlp->nlp_flag |= NLP_UNREG_INP;

			lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
					 "1433 unreg_rpi UNREG x%x on "
					 "NPort x%x deferred flg x%x "
					 "Data:x%px\n",
					 ndlp->nlp_rpi, ndlp->nlp_DID,
					 ndlp->nlp_flag, ndlp);

			rc = lpfc_sli_issue_mbox(phba, mbox, MBX_NOWAIT);
			if (rc == MBX_NOT_FINISHED) {
				mempool_free(mbox, phba->mbox_mem_pool);
				acc_plogi = 1;
			}
		}
		lpfc_no_rpi(phba, ndlp);
out:
		if (phba->sli_rev != LPFC_SLI_REV4)
			ndlp->nlp_rpi = 0;
		ndlp->nlp_flag &= ~NLP_RPI_REGISTERED;
		ndlp->nlp_flag &= ~NLP_NPR_ADISC;
		if (acc_plogi)
			ndlp->nlp_flag &= ~NLP_LOGO_ACC;
		return 1;
	}
	ndlp->nlp_flag &= ~NLP_LOGO_ACC;
	return 0;
}