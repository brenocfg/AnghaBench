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
typedef  int uint32_t ;
struct lpfc_register {scalar_t__ word0; } ;
struct lpfc_queue {int queue_id; TYPE_2__* phba; } ;
struct lpfc_hba {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  CQDBregaddr; } ;
struct TYPE_4__ {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int LPFC_CQID_HI_FIELD_SHIFT ; 
 int LPFC_QUEUE_TYPE_COMPLETION ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct lpfc_register*,int) ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_arm ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_cqid_hi ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_cqid_lo ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_num_released ; 
 int /*<<< orphan*/  lpfc_eqcq_doorbell_qt ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

void
lpfc_sli4_write_cq_db(struct lpfc_hba *phba, struct lpfc_queue *q,
		     uint32_t count, bool arm)
{
	struct lpfc_register doorbell;

	/* sanity check on queue memory */
	if (unlikely(!q || (count == 0 && !arm)))
		return;

	/* ring doorbell for number popped */
	doorbell.word0 = 0;
	if (arm)
		bf_set(lpfc_eqcq_doorbell_arm, &doorbell, 1);
	bf_set(lpfc_eqcq_doorbell_num_released, &doorbell, count);
	bf_set(lpfc_eqcq_doorbell_qt, &doorbell, LPFC_QUEUE_TYPE_COMPLETION);
	bf_set(lpfc_eqcq_doorbell_cqid_hi, &doorbell,
			(q->queue_id >> LPFC_CQID_HI_FIELD_SHIFT));
	bf_set(lpfc_eqcq_doorbell_cqid_lo, &doorbell, q->queue_id);
	writel(doorbell.word0, q->phba->sli4_hba.CQDBregaddr);
}