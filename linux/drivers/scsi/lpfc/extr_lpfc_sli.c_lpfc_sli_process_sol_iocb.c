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
struct lpfc_sli_ring {scalar_t__ ringno; } ;
struct TYPE_3__ {void** ulpWord; } ;
struct TYPE_4__ {scalar_t__ ulpCommand; int /*<<< orphan*/  ulpContext; TYPE_1__ un; void* ulpStatus; int /*<<< orphan*/  ulpIoTag; } ;
struct lpfc_iocbq {int iocb_flag; TYPE_2__ iocb; int /*<<< orphan*/  (* iocb_cmpl ) (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ;} ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  hbalock; } ;

/* Variables and functions */
 scalar_t__ CMD_ELS_REQUEST64_CR ; 
 void* IOERR_ABORT_REQUESTED ; 
 void* IOERR_SLI_ABORTED ; 
 void* IOSTAT_LOCAL_REJECT ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int LPFC_DELAY_MEM_FREE ; 
 int LPFC_DRIVER_ABORTED ; 
 scalar_t__ LPFC_ELS_RING ; 
 int LPFC_EXCHANGE_BUSY ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,void*,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_send_els_failure_event (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ; 
 struct lpfc_iocbq* lpfc_sli_iocbq_lookup (struct lpfc_hba*,struct lpfc_sli_ring*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_sli_release_iocbq (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ; 

__attribute__((used)) static int
lpfc_sli_process_sol_iocb(struct lpfc_hba *phba, struct lpfc_sli_ring *pring,
			  struct lpfc_iocbq *saveq)
{
	struct lpfc_iocbq *cmdiocbp;
	int rc = 1;
	unsigned long iflag;

	cmdiocbp = lpfc_sli_iocbq_lookup(phba, pring, saveq);
	if (cmdiocbp) {
		if (cmdiocbp->iocb_cmpl) {
			/*
			 * If an ELS command failed send an event to mgmt
			 * application.
			 */
			if (saveq->iocb.ulpStatus &&
			     (pring->ringno == LPFC_ELS_RING) &&
			     (cmdiocbp->iocb.ulpCommand ==
				CMD_ELS_REQUEST64_CR))
				lpfc_send_els_failure_event(phba,
					cmdiocbp, saveq);

			/*
			 * Post all ELS completions to the worker thread.
			 * All other are passed to the completion callback.
			 */
			if (pring->ringno == LPFC_ELS_RING) {
				if ((phba->sli_rev < LPFC_SLI_REV4) &&
				    (cmdiocbp->iocb_flag &
							LPFC_DRIVER_ABORTED)) {
					spin_lock_irqsave(&phba->hbalock,
							  iflag);
					cmdiocbp->iocb_flag &=
						~LPFC_DRIVER_ABORTED;
					spin_unlock_irqrestore(&phba->hbalock,
							       iflag);
					saveq->iocb.ulpStatus =
						IOSTAT_LOCAL_REJECT;
					saveq->iocb.un.ulpWord[4] =
						IOERR_SLI_ABORTED;

					/* Firmware could still be in progress
					 * of DMAing payload, so don't free data
					 * buffer till after a hbeat.
					 */
					spin_lock_irqsave(&phba->hbalock,
							  iflag);
					saveq->iocb_flag |= LPFC_DELAY_MEM_FREE;
					spin_unlock_irqrestore(&phba->hbalock,
							       iflag);
				}
				if (phba->sli_rev == LPFC_SLI_REV4) {
					if (saveq->iocb_flag &
					    LPFC_EXCHANGE_BUSY) {
						/* Set cmdiocb flag for the
						 * exchange busy so sgl (xri)
						 * will not be released until
						 * the abort xri is received
						 * from hba.
						 */
						spin_lock_irqsave(
							&phba->hbalock, iflag);
						cmdiocbp->iocb_flag |=
							LPFC_EXCHANGE_BUSY;
						spin_unlock_irqrestore(
							&phba->hbalock, iflag);
					}
					if (cmdiocbp->iocb_flag &
					    LPFC_DRIVER_ABORTED) {
						/*
						 * Clear LPFC_DRIVER_ABORTED
						 * bit in case it was driver
						 * initiated abort.
						 */
						spin_lock_irqsave(
							&phba->hbalock, iflag);
						cmdiocbp->iocb_flag &=
							~LPFC_DRIVER_ABORTED;
						spin_unlock_irqrestore(
							&phba->hbalock, iflag);
						cmdiocbp->iocb.ulpStatus =
							IOSTAT_LOCAL_REJECT;
						cmdiocbp->iocb.un.ulpWord[4] =
							IOERR_ABORT_REQUESTED;
						/*
						 * For SLI4, irsiocb contains
						 * NO_XRI in sli_xritag, it
						 * shall not affect releasing
						 * sgl (xri) process.
						 */
						saveq->iocb.ulpStatus =
							IOSTAT_LOCAL_REJECT;
						saveq->iocb.un.ulpWord[4] =
							IOERR_SLI_ABORTED;
						spin_lock_irqsave(
							&phba->hbalock, iflag);
						saveq->iocb_flag |=
							LPFC_DELAY_MEM_FREE;
						spin_unlock_irqrestore(
							&phba->hbalock, iflag);
					}
				}
			}
			(cmdiocbp->iocb_cmpl) (phba, cmdiocbp, saveq);
		} else
			lpfc_sli_release_iocbq(phba, cmdiocbp);
	} else {
		/*
		 * Unknown initiating command based on the response iotag.
		 * This could be the case on the ELS ring because of
		 * lpfc_els_abort().
		 */
		if (pring->ringno != LPFC_ELS_RING) {
			/*
			 * Ring <ringno> handler: unexpected completion IoTag
			 * <IoTag>
			 */
			lpfc_printf_log(phba, KERN_WARNING, LOG_SLI,
					 "0322 Ring %d handler: "
					 "unexpected completion IoTag x%x "
					 "Data: x%x x%x x%x x%x\n",
					 pring->ringno,
					 saveq->iocb.ulpIoTag,
					 saveq->iocb.ulpStatus,
					 saveq->iocb.un.ulpWord[4],
					 saveq->iocb.ulpCommand,
					 saveq->iocb.ulpContext);
		}
	}

	return rc;
}