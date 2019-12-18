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
struct lpfc_sli_ring {int dummy; } ;
struct TYPE_4__ {struct lpfc_sli_ring* sli3_ring; } ;
struct TYPE_6__ {TYPE_2__* els_wq; } ;
struct lpfc_hba {scalar_t__ sli_rev; TYPE_1__ sli; TYPE_3__ sli4_hba; } ;
struct TYPE_5__ {struct lpfc_sli_ring* pring; } ;

/* Variables and functions */
 size_t LPFC_ELS_RING ; 
 scalar_t__ LPFC_SLI_REV2 ; 
 scalar_t__ LPFC_SLI_REV3 ; 
 scalar_t__ LPFC_SLI_REV4 ; 

__attribute__((used)) static inline struct lpfc_sli_ring *
lpfc_phba_elsring(struct lpfc_hba *phba)
{
	/* Return NULL if sli_rev has become invalid due to bad fw */
	if (phba->sli_rev != LPFC_SLI_REV4  &&
	    phba->sli_rev != LPFC_SLI_REV3  &&
	    phba->sli_rev != LPFC_SLI_REV2)
		return NULL;

	if (phba->sli_rev == LPFC_SLI_REV4) {
		if (phba->sli4_hba.els_wq)
			return phba->sli4_hba.els_wq->pring;
		else
			return NULL;
	}
	return &phba->sli.sli3_ring[LPFC_ELS_RING];
}