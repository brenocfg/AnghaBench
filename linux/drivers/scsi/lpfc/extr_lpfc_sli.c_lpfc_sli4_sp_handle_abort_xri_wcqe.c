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
struct sli4_wcqe_xri_aborted {int /*<<< orphan*/  word3; int /*<<< orphan*/  word2; int /*<<< orphan*/  parameter; int /*<<< orphan*/  word0; } ;
struct lpfc_queue {int subtype; int /*<<< orphan*/  hdwq; } ;
struct TYPE_2__ {int /*<<< orphan*/  sp_els_xri_aborted_work_queue; } ;
struct lpfc_hba {int cfg_enable_fc4_type; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  hba_flag; TYPE_1__ sli4_hba; int /*<<< orphan*/  nvmet_support; } ;
struct lpfc_cq_event {int /*<<< orphan*/  list; int /*<<< orphan*/  hdwq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_XRI_ABORT_EVENT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
#define  LPFC_ELS 130 
 int LPFC_ENABLE_NVME ; 
#define  LPFC_IO 129 
#define  LPFC_NVME_LS 128 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lpfc_cq_event* lpfc_cq_event_setup (struct lpfc_hba*,struct sli4_wcqe_xri_aborted*,int) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_io_xri_aborted (struct lpfc_hba*,struct sli4_wcqe_xri_aborted*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_nvmet_xri_aborted (struct lpfc_hba*,struct sli4_wcqe_xri_aborted*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool
lpfc_sli4_sp_handle_abort_xri_wcqe(struct lpfc_hba *phba,
				   struct lpfc_queue *cq,
				   struct sli4_wcqe_xri_aborted *wcqe)
{
	bool workposted = false;
	struct lpfc_cq_event *cq_event;
	unsigned long iflags;

	switch (cq->subtype) {
	case LPFC_IO:
		lpfc_sli4_io_xri_aborted(phba, wcqe, cq->hdwq);
		if (phba->cfg_enable_fc4_type & LPFC_ENABLE_NVME) {
			/* Notify aborted XRI for NVME work queue */
			if (phba->nvmet_support)
				lpfc_sli4_nvmet_xri_aborted(phba, wcqe);
		}
		workposted = false;
		break;
	case LPFC_NVME_LS: /* NVME LS uses ELS resources */
	case LPFC_ELS:
		cq_event = lpfc_cq_event_setup(
			phba, wcqe, sizeof(struct sli4_wcqe_xri_aborted));
		if (!cq_event)
			return false;
		cq_event->hdwq = cq->hdwq;
		spin_lock_irqsave(&phba->hbalock, iflags);
		list_add_tail(&cq_event->list,
			      &phba->sli4_hba.sp_els_xri_aborted_work_queue);
		/* Set the els xri abort event flag */
		phba->hba_flag |= ELS_XRI_ABORT_EVENT;
		spin_unlock_irqrestore(&phba->hbalock, iflags);
		workposted = true;
		break;
	default:
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"0603 Invalid CQ subtype %d: "
				"%08x %08x %08x %08x\n",
				cq->subtype, wcqe->word0, wcqe->parameter,
				wcqe->word2, wcqe->word3);
		workposted = false;
		break;
	}
	return workposted;
}