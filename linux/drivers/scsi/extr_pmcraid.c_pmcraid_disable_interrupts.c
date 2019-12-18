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
struct TYPE_2__ {int /*<<< orphan*/  ioa_host_interrupt_mask_reg; int /*<<< orphan*/  global_interrupt_mask_reg; int /*<<< orphan*/  ioa_host_interrupt_clr_reg; } ;
struct pmcraid_instance {TYPE_1__ int_regs; int /*<<< orphan*/  interrupt_mode; } ;

/* Variables and functions */
 int GLOBAL_INTERRUPT_MASK ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmcraid_disable_interrupts(
	struct pmcraid_instance *pinstance,
	u32 intrs
)
{
	u32 gmask = ioread32(pinstance->int_regs.global_interrupt_mask_reg);
	u32 nmask = gmask | GLOBAL_INTERRUPT_MASK;

	iowrite32(intrs, pinstance->int_regs.ioa_host_interrupt_clr_reg);
	iowrite32(nmask, pinstance->int_regs.global_interrupt_mask_reg);
	ioread32(pinstance->int_regs.global_interrupt_mask_reg);

	if (!pinstance->interrupt_mode) {
		iowrite32(intrs,
			pinstance->int_regs.ioa_host_interrupt_mask_reg);
		ioread32(pinstance->int_regs.ioa_host_interrupt_mask_reg);
	}
}