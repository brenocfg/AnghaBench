#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fintek_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIR_STATUS ; 
 int /*<<< orphan*/  CIR_STATUS_IRQ_MASK ; 
 int /*<<< orphan*/  fintek_cir_reg_write (struct fintek_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fintek_enable_cir_irq (struct fintek_dev*) ; 

__attribute__((used)) static void fintek_cir_regs_init(struct fintek_dev *fintek)
{
	/* clear any and all stray interrupts */
	fintek_cir_reg_write(fintek, CIR_STATUS_IRQ_MASK, CIR_STATUS);

	/* and finally, enable interrupts */
	fintek_enable_cir_irq(fintek);
}