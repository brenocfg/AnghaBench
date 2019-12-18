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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  host_ioa_interrupt_reg; int /*<<< orphan*/  ioa_host_interrupt_reg; int /*<<< orphan*/  ioa_host_interrupt_mask_reg; } ;
struct pmcraid_instance {int ioa_hard_reset; int ioa_unit_check; TYPE_1__ int_regs; } ;

/* Variables and functions */
 int DOORBELL_IOA_RESET_ALERT ; 
 int INTRS_HRRQ_VALID ; 
 int INTRS_IOA_UNIT_CHECK ; 
 int PMCRAID_ERROR_INTERRUPTS ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_info (char*) ; 

__attribute__((used)) static void pmcraid_reset_type(struct pmcraid_instance *pinstance)
{
	u32 mask;
	u32 intrs;
	u32 alerts;

	mask = ioread32(pinstance->int_regs.ioa_host_interrupt_mask_reg);
	intrs = ioread32(pinstance->int_regs.ioa_host_interrupt_reg);
	alerts = ioread32(pinstance->int_regs.host_ioa_interrupt_reg);

	if ((mask & INTRS_HRRQ_VALID) == 0 ||
	    (alerts & DOORBELL_IOA_RESET_ALERT) ||
	    (intrs & PMCRAID_ERROR_INTERRUPTS)) {
		pmcraid_info("IOA requires hard reset\n");
		pinstance->ioa_hard_reset = 1;
	}

	/* If unit check is active, trigger the dump */
	if (intrs & INTRS_IOA_UNIT_CHECK)
		pinstance->ioa_unit_check = 1;
}