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
struct TYPE_3__ {int /*<<< orphan*/  vpi_used; } ;
struct TYPE_4__ {TYPE_1__ max_cfg_param; } ;
struct lpfc_hba {int max_vpi; scalar_t__ sli_rev; int /*<<< orphan*/  hbalock; TYPE_2__ sli4_hba; int /*<<< orphan*/  vpi_bmask; } ;

/* Variables and functions */
 scalar_t__ LPFC_SLI_REV4 ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
lpfc_alloc_vpi(struct lpfc_hba *phba)
{
	unsigned long vpi;

	spin_lock_irq(&phba->hbalock);
	/* Start at bit 1 because vpi zero is reserved for the physical port */
	vpi = find_next_zero_bit(phba->vpi_bmask, (phba->max_vpi + 1), 1);
	if (vpi > phba->max_vpi)
		vpi = 0;
	else
		set_bit(vpi, phba->vpi_bmask);
	if (phba->sli_rev == LPFC_SLI_REV4)
		phba->sli4_hba.max_cfg_param.vpi_used++;
	spin_unlock_irq(&phba->hbalock);
	return vpi;
}