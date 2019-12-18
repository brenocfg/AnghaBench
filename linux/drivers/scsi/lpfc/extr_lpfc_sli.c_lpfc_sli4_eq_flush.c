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
struct lpfc_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sli4_write_eq_db ) (struct lpfc_hba*,struct lpfc_queue*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;
struct lpfc_eqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_QUEUE_REARM ; 
 int /*<<< orphan*/  __lpfc_sli4_consume_eqe (struct lpfc_hba*,struct lpfc_queue*,struct lpfc_eqe*) ; 
 struct lpfc_eqe* lpfc_sli4_eq_get (struct lpfc_queue*) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_hba*,struct lpfc_queue*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_sli4_eq_flush(struct lpfc_hba *phba, struct lpfc_queue *eq)
{
	struct lpfc_eqe *eqe;
	uint32_t count = 0;

	/* walk all the EQ entries and drop on the floor */
	eqe = lpfc_sli4_eq_get(eq);
	while (eqe) {
		__lpfc_sli4_consume_eqe(phba, eq, eqe);
		count++;
		eqe = lpfc_sli4_eq_get(eq);
	}

	/* Clear and re-arm the EQ */
	phba->sli4_hba.sli4_write_eq_db(phba, eq, count, LPFC_QUEUE_REARM);
}