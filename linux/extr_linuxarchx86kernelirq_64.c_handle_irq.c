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
struct pt_regs {int dummy; } ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq_desc (struct irq_desc*) ; 
 int /*<<< orphan*/  stack_overflow_check (struct pt_regs*) ; 

bool handle_irq(struct irq_desc *desc, struct pt_regs *regs)
{
	stack_overflow_check(regs);

	if (IS_ERR_OR_NULL(desc))
		return false;

	generic_handle_irq_desc(desc);
	return true;
}