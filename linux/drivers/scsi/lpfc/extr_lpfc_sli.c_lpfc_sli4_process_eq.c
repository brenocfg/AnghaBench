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
struct lpfc_queue {int max_proc_limit; int notify_interval; int EQ_processed; int EQ_max_eqe; scalar_t__ queue_claimed; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sli4_write_eq_db ) (struct lpfc_hba*,struct lpfc_queue*,int,int /*<<< orphan*/ ) ;} ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;
struct lpfc_eqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_QUEUE_NOARM ; 
 int /*<<< orphan*/  LPFC_QUEUE_REARM ; 
 int /*<<< orphan*/  __lpfc_sli4_consume_eqe (struct lpfc_hba*,struct lpfc_queue*,struct lpfc_eqe*) ; 
 scalar_t__ cmpxchg (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 struct lpfc_eqe* lpfc_sli4_eq_get (struct lpfc_queue*) ; 
 int /*<<< orphan*/  lpfc_sli4_hba_handle_eqe (struct lpfc_hba*,struct lpfc_queue*,struct lpfc_eqe*) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_hba*,struct lpfc_queue*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct lpfc_hba*,struct lpfc_queue*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_sli4_process_eq(struct lpfc_hba *phba, struct lpfc_queue *eq)
{
	struct lpfc_eqe *eqe;
	int count = 0, consumed = 0;

	if (cmpxchg(&eq->queue_claimed, 0, 1) != 0)
		goto rearm_and_exit;

	eqe = lpfc_sli4_eq_get(eq);
	while (eqe) {
		lpfc_sli4_hba_handle_eqe(phba, eq, eqe);
		__lpfc_sli4_consume_eqe(phba, eq, eqe);

		consumed++;
		if (!(++count % eq->max_proc_limit))
			break;

		if (!(count % eq->notify_interval)) {
			phba->sli4_hba.sli4_write_eq_db(phba, eq, consumed,
							LPFC_QUEUE_NOARM);
			consumed = 0;
		}

		eqe = lpfc_sli4_eq_get(eq);
	}
	eq->EQ_processed += count;

	/* Track the max number of EQEs processed in 1 intr */
	if (count > eq->EQ_max_eqe)
		eq->EQ_max_eqe = count;

	eq->queue_claimed = 0;

rearm_and_exit:
	/* Always clear and re-arm the EQ */
	phba->sli4_hba.sli4_write_eq_db(phba, eq, consumed, LPFC_QUEUE_REARM);

	return count;
}