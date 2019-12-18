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
typedef  scalar_t__ uint32_t ;
struct lpfc_sli_ring {int num_mask; TYPE_1__* prt; } ;
struct lpfc_iocbq {int dummy; } ;
struct lpfc_hba {int dummy; } ;
struct TYPE_2__ {scalar_t__ rctl; scalar_t__ type; int /*<<< orphan*/  (* lpfc_sli_rcv_unsol_event ) (struct lpfc_hba*,struct lpfc_sli_ring*,struct lpfc_iocbq*) ;scalar_t__ profile; } ;

/* Variables and functions */
#define  FC_TYPE_NVME 128 
 int /*<<< orphan*/  lpfc_nvmet_unsol_ls_event (struct lpfc_hba*,struct lpfc_sli_ring*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_hba*,struct lpfc_sli_ring*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  stub2 (struct lpfc_hba*,struct lpfc_sli_ring*,struct lpfc_iocbq*) ; 

__attribute__((used)) static int
lpfc_complete_unsol_iocb(struct lpfc_hba *phba, struct lpfc_sli_ring *pring,
			 struct lpfc_iocbq *saveq, uint32_t fch_r_ctl,
			 uint32_t fch_type)
{
	int i;

	switch (fch_type) {
	case FC_TYPE_NVME:
		lpfc_nvmet_unsol_ls_event(phba, pring, saveq);
		return 1;
	default:
		break;
	}

	/* unSolicited Responses */
	if (pring->prt[0].profile) {
		if (pring->prt[0].lpfc_sli_rcv_unsol_event)
			(pring->prt[0].lpfc_sli_rcv_unsol_event) (phba, pring,
									saveq);
		return 1;
	}
	/* We must search, based on rctl / type
	   for the right routine */
	for (i = 0; i < pring->num_mask; i++) {
		if ((pring->prt[i].rctl == fch_r_ctl) &&
		    (pring->prt[i].type == fch_type)) {
			if (pring->prt[i].lpfc_sli_rcv_unsol_event)
				(pring->prt[i].lpfc_sli_rcv_unsol_event)
						(phba, pring, saveq);
			return 1;
		}
	}
	return 0;
}