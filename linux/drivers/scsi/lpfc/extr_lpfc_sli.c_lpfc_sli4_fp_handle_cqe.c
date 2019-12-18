#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sli4_wcqe_xri_aborted {int dummy; } ;
struct lpfc_wcqe_release {int dummy; } ;
struct lpfc_wcqe_complete {int dummy; } ;
struct lpfc_rcqe {int dummy; } ;
struct lpfc_queue {int /*<<< orphan*/  subtype; int /*<<< orphan*/  CQ_xri_aborted; int /*<<< orphan*/  CQ_release_wqe; int /*<<< orphan*/  CQ_wq; } ;
struct lpfc_hba {void* last_completion_time; } ;
struct lpfc_cqe {int dummy; } ;

/* Variables and functions */
#define  CQE_CODE_COMPL_WQE 133 
#define  CQE_CODE_NVME_ERSP 132 
#define  CQE_CODE_RECEIVE 131 
#define  CQE_CODE_RECEIVE_V1 130 
#define  CQE_CODE_RELEASE_WQE 129 
#define  CQE_CODE_XRI_ABORTED 128 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int /*<<< orphan*/  LPFC_IO ; 
 int /*<<< orphan*/  LPFC_NVMET ; 
 int /*<<< orphan*/  LPFC_NVME_LS ; 
 int bf_get (int /*<<< orphan*/ ,struct lpfc_wcqe_release*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lpfc_sli4_fp_handle_fcp_wcqe (struct lpfc_hba*,struct lpfc_queue*,struct lpfc_wcqe_complete*) ; 
 int /*<<< orphan*/  lpfc_sli4_fp_handle_rel_wcqe (struct lpfc_hba*,struct lpfc_queue*,struct lpfc_wcqe_release*) ; 
 int lpfc_sli4_nvmet_handle_rcqe (struct lpfc_hba*,struct lpfc_queue*,struct lpfc_rcqe*) ; 
 int /*<<< orphan*/  lpfc_sli4_pcimem_bcopy (struct lpfc_cqe*,struct lpfc_wcqe_release*,int) ; 
 int lpfc_sli4_sp_handle_abort_xri_wcqe (struct lpfc_hba*,struct lpfc_queue*,struct sli4_wcqe_xri_aborted*) ; 
 int /*<<< orphan*/  lpfc_wcqe_c_code ; 

__attribute__((used)) static bool
lpfc_sli4_fp_handle_cqe(struct lpfc_hba *phba, struct lpfc_queue *cq,
			 struct lpfc_cqe *cqe)
{
	struct lpfc_wcqe_release wcqe;
	bool workposted = false;

	/* Copy the work queue CQE and convert endian order if needed */
	lpfc_sli4_pcimem_bcopy(cqe, &wcqe, sizeof(struct lpfc_cqe));

	/* Check and process for different type of WCQE and dispatch */
	switch (bf_get(lpfc_wcqe_c_code, &wcqe)) {
	case CQE_CODE_COMPL_WQE:
	case CQE_CODE_NVME_ERSP:
		cq->CQ_wq++;
		/* Process the WQ complete event */
		phba->last_completion_time = jiffies;
		if (cq->subtype == LPFC_IO || cq->subtype == LPFC_NVME_LS)
			lpfc_sli4_fp_handle_fcp_wcqe(phba, cq,
				(struct lpfc_wcqe_complete *)&wcqe);
		break;
	case CQE_CODE_RELEASE_WQE:
		cq->CQ_release_wqe++;
		/* Process the WQ release event */
		lpfc_sli4_fp_handle_rel_wcqe(phba, cq,
				(struct lpfc_wcqe_release *)&wcqe);
		break;
	case CQE_CODE_XRI_ABORTED:
		cq->CQ_xri_aborted++;
		/* Process the WQ XRI abort event */
		phba->last_completion_time = jiffies;
		workposted = lpfc_sli4_sp_handle_abort_xri_wcqe(phba, cq,
				(struct sli4_wcqe_xri_aborted *)&wcqe);
		break;
	case CQE_CODE_RECEIVE_V1:
	case CQE_CODE_RECEIVE:
		phba->last_completion_time = jiffies;
		if (cq->subtype == LPFC_NVMET) {
			workposted = lpfc_sli4_nvmet_handle_rcqe(
				phba, cq, (struct lpfc_rcqe *)&wcqe);
		}
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"0144 Not a valid CQE code: x%x\n",
				bf_get(lpfc_wcqe_c_code, &wcqe));
		break;
	}
	return workposted;
}