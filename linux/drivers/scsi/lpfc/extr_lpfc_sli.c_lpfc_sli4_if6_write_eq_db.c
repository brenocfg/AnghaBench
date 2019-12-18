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
struct TYPE_3__ {int /*<<< orphan*/  EQDBregaddr; } ;
struct TYPE_4__ {scalar_t__ intr_type; TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 scalar_t__ INTx ; 
 int LPFC_QUEUE_REARM ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct lpfc_register*,int) ; 
 int /*<<< orphan*/  lpfc_if6_eq_doorbell_arm ; 
 int /*<<< orphan*/  lpfc_if6_eq_doorbell_eqid ; 
 int /*<<< orphan*/  lpfc_if6_eq_doorbell_num_released ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

void
lpfc_sli4_if6_write_eq_db(struct lpfc_hba *phba, struct lpfc_queue *q,
			  uint32_t count, bool arm)
{
	struct lpfc_register doorbell;

	/* sanity check on queue memory */
	if (unlikely(!q || (count == 0 && !arm)))
		return;

	/* ring doorbell for number popped */
	doorbell.word0 = 0;
	if (arm)
		bf_set(lpfc_if6_eq_doorbell_arm, &doorbell, 1);
	bf_set(lpfc_if6_eq_doorbell_num_released, &doorbell, count);
	bf_set(lpfc_if6_eq_doorbell_eqid, &doorbell, q->queue_id);
	writel(doorbell.word0, q->phba->sli4_hba.EQDBregaddr);
	/* PCI read to flush PCI pipeline on re-arming for INTx mode */
	if ((q->phba->intr_type == INTx) && (arm == LPFC_QUEUE_REARM))
		readl(q->phba->sli4_hba.EQDBregaddr);
}