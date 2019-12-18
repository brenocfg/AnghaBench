#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lpfc_sli_ring {int dummy; } ;
struct lpfc_iocbq {int iocb_flag; size_t hba_wqidx; scalar_t__ context1; } ;
struct lpfc_io_buf {size_t hdwq_no; } ;
struct TYPE_8__ {TYPE_3__* els_wq; TYPE_2__* hdwq; } ;
struct lpfc_hba {TYPE_4__ sli4_hba; } ;
struct TYPE_7__ {struct lpfc_sli_ring* pring; } ;
struct TYPE_6__ {TYPE_1__* io_wq; } ;
struct TYPE_5__ {struct lpfc_sli_ring* pring; } ;

/* Variables and functions */
 int LPFC_IO_FCP ; 
 int LPFC_USE_FCPWQIDX ; 
 scalar_t__ unlikely (int) ; 

struct lpfc_sli_ring *
lpfc_sli4_calc_ring(struct lpfc_hba *phba, struct lpfc_iocbq *piocb)
{
	struct lpfc_io_buf *lpfc_cmd;

	if (piocb->iocb_flag & (LPFC_IO_FCP | LPFC_USE_FCPWQIDX)) {
		if (unlikely(!phba->sli4_hba.hdwq))
			return NULL;
		/*
		 * for abort iocb hba_wqidx should already
		 * be setup based on what work queue we used.
		 */
		if (!(piocb->iocb_flag & LPFC_USE_FCPWQIDX)) {
			lpfc_cmd = (struct lpfc_io_buf *)piocb->context1;
			piocb->hba_wqidx = lpfc_cmd->hdwq_no;
		}
		return phba->sli4_hba.hdwq[piocb->hba_wqidx].io_wq->pring;
	} else {
		if (unlikely(!phba->sli4_hba.els_wq))
			return NULL;
		piocb->hba_wqidx = 0;
		return phba->sli4_hba.els_wq->pring;
	}
}