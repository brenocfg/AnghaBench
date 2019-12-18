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
struct lpfc_register {scalar_t__ word0; } ;
struct lpfc_queue {TYPE_2__* phba; int /*<<< orphan*/  queue_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  EQDBregaddr; } ;
struct TYPE_4__ {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct lpfc_register*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_if6_eq_doorbell_eqid ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

void
lpfc_sli4_if6_eq_clr_intr(struct lpfc_queue *q)
{
	struct lpfc_register doorbell;

	doorbell.word0 = 0;
	bf_set(lpfc_if6_eq_doorbell_eqid, &doorbell, q->queue_id);
	writel(doorbell.word0, q->phba->sli4_hba.EQDBregaddr);
}