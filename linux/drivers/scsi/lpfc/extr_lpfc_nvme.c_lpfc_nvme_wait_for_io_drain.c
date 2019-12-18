#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct lpfc_sli_ring {int /*<<< orphan*/  txcmplq; } ;
struct TYPE_6__ {TYPE_2__* hdwq; } ;
struct lpfc_hba {scalar_t__ sli_rev; size_t cfg_hdw_queue; TYPE_3__ sli4_hba; } ;
struct TYPE_5__ {TYPE_1__* io_wq; } ;
struct TYPE_4__ {struct lpfc_sli_ring* pring; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_NVME_IOERR ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  LPFC_XRI_EXCH_BUSY_WAIT_T1 ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

void
lpfc_nvme_wait_for_io_drain(struct lpfc_hba *phba)
{
	struct lpfc_sli_ring  *pring;
	u32 i, wait_cnt = 0;

	if (phba->sli_rev < LPFC_SLI_REV4 || !phba->sli4_hba.hdwq)
		return;

	/* Cycle through all IO rings and make sure all outstanding
	 * WQEs have been removed from the txcmplqs.
	 */
	for (i = 0; i < phba->cfg_hdw_queue; i++) {
		if (!phba->sli4_hba.hdwq[i].io_wq)
			continue;
		pring = phba->sli4_hba.hdwq[i].io_wq->pring;

		if (!pring)
			continue;

		/* Retrieve everything on the txcmplq */
		while (!list_empty(&pring->txcmplq)) {
			msleep(LPFC_XRI_EXCH_BUSY_WAIT_T1);
			wait_cnt++;

			/* The sleep is 10mS.  Every ten seconds,
			 * dump a message.  Something is wrong.
			 */
			if ((wait_cnt % 1000) == 0) {
				lpfc_printf_log(phba, KERN_ERR, LOG_NVME_IOERR,
						"6178 NVME IO not empty, "
						"cnt %d\n", wait_cnt);
			}
		}
	}
}