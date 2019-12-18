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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  sense_interrupt_reg; int /*<<< orphan*/  clr_interrupt_reg32; int /*<<< orphan*/  clr_interrupt_reg; int /*<<< orphan*/  set_interrupt_mask_reg; } ;
struct ipr_ioa_cfg {int hrrq_num; TYPE_2__ regs; scalar_t__ sis64; TYPE_1__* hrrq; } ;
struct TYPE_3__ {int /*<<< orphan*/  _lock; scalar_t__ allow_interrupts; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipr_mask_and_clear_interrupts(struct ipr_ioa_cfg *ioa_cfg,
					  u32 clr_ints)
{
	volatile u32 int_reg;
	int i;

	/* Stop new interrupts */
	for (i = 0; i < ioa_cfg->hrrq_num; i++) {
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].allow_interrupts = 0;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	}

	/* Set interrupt mask to stop all new interrupts */
	if (ioa_cfg->sis64)
		writeq(~0, ioa_cfg->regs.set_interrupt_mask_reg);
	else
		writel(~0, ioa_cfg->regs.set_interrupt_mask_reg);

	/* Clear any pending interrupts */
	if (ioa_cfg->sis64)
		writel(~0, ioa_cfg->regs.clr_interrupt_reg);
	writel(clr_ints, ioa_cfg->regs.clr_interrupt_reg32);
	int_reg = readl(ioa_cfg->regs.sense_interrupt_reg);
}