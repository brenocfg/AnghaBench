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
struct tc3589x {int /*<<< orphan*/  domain; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  TC3589x_IRQST ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  handle_nested_irq (int) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int tc3589x_reg_read (struct tc3589x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tc3589x_irq(int irq, void *data)
{
	struct tc3589x *tc3589x = data;
	int status;

again:
	status = tc3589x_reg_read(tc3589x, TC3589x_IRQST);
	if (status < 0)
		return IRQ_NONE;

	while (status) {
		int bit = __ffs(status);
		int virq = irq_create_mapping(tc3589x->domain, bit);

		handle_nested_irq(virq);
		status &= ~(1 << bit);
	}

	/*
	 * A dummy read or write (to any register) appears to be necessary to
	 * have the last interrupt clear (for example, GPIO IC write) take
	 * effect. In such a case, recheck for any interrupt which is still
	 * pending.
	 */
	status = tc3589x_reg_read(tc3589x, TC3589x_IRQST);
	if (status)
		goto again;

	return IRQ_HANDLED;
}