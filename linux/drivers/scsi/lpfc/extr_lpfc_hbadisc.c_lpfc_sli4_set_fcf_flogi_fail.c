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
typedef  size_t uint16_t ;
struct TYPE_3__ {struct lpfc_fcf_pri* fcf_pri; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; TYPE_1__ fcf; } ;
struct TYPE_4__ {int /*<<< orphan*/  flag; } ;
struct lpfc_fcf_pri {TYPE_2__ fcf_rec; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_FCF_FLOGI_FAILED ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
lpfc_sli4_set_fcf_flogi_fail(struct lpfc_hba *phba, uint16_t fcf_index)
{
	struct lpfc_fcf_pri *new_fcf_pri;
	new_fcf_pri = &phba->fcf.fcf_pri[fcf_index];
	spin_lock_irq(&phba->hbalock);
	new_fcf_pri->fcf_rec.flag |= LPFC_FCF_FLOGI_FAILED;
	spin_unlock_irq(&phba->hbalock);
}