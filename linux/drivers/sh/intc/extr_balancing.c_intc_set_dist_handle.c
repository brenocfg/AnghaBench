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
struct intc_desc_int {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask_regs; } ;
struct intc_desc {TYPE_1__ hw; } ;
typedef  int /*<<< orphan*/  intc_enum ;

/* Variables and functions */
 int /*<<< orphan*/ * dist_handle ; 
 int /*<<< orphan*/  intc_big_lock ; 
 int /*<<< orphan*/  intc_dist_data (struct intc_desc*,struct intc_desc_int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void intc_set_dist_handle(unsigned int irq, struct intc_desc *desc,
			  struct intc_desc_int *d, intc_enum id)
{
	unsigned long flags;

	/*
	 * Nothing to do for this IRQ.
	 */
	if (!desc->hw.mask_regs)
		return;

	raw_spin_lock_irqsave(&intc_big_lock, flags);
	dist_handle[irq] = intc_dist_data(desc, d, id);
	raw_spin_unlock_irqrestore(&intc_big_lock, flags);
}