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
struct TYPE_4__ {struct lpfc_hba* sli3_ring; } ;
struct TYPE_3__ {struct lpfc_hba* hdwq; } ;
struct lpfc_hba {scalar_t__ sli_rev; TYPE_2__ sli; int /*<<< orphan*/  brd_no; TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_hba_index ; 

__attribute__((used)) static void
lpfc_hba_free(struct lpfc_hba *phba)
{
	if (phba->sli_rev == LPFC_SLI_REV4)
		kfree(phba->sli4_hba.hdwq);

	/* Release the driver assigned board number */
	idr_remove(&lpfc_hba_index, phba->brd_no);

	/* Free memory allocated with sli3 rings */
	kfree(phba->sli.sli3_ring);
	phba->sli.sli3_ring = NULL;

	kfree(phba);
	return;
}