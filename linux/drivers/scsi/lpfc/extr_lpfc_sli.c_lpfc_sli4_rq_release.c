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
typedef  int uint32_t ;
struct lpfc_queue {scalar_t__ type; int hba_index; int entry_count; } ;

/* Variables and functions */
 scalar_t__ LPFC_DRQ ; 
 scalar_t__ LPFC_HRQ ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static uint32_t
lpfc_sli4_rq_release(struct lpfc_queue *hq, struct lpfc_queue *dq)
{
	/* sanity check on queue memory */
	if (unlikely(!hq) || unlikely(!dq))
		return 0;

	if ((hq->type != LPFC_HRQ) || (dq->type != LPFC_DRQ))
		return 0;
	hq->hba_index = ((hq->hba_index + 1) % hq->entry_count);
	dq->hba_index = ((dq->hba_index + 1) % dq->entry_count);
	return 1;
}