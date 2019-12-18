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
struct irq_data {int dummy; } ;
struct intc_handle_int {int /*<<< orphan*/  handle; } ;
struct intc_desc_int {int /*<<< orphan*/  nr_prio; int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ REG_FN_ERR ; 
 scalar_t__ _INTC_FN (int /*<<< orphan*/ ) ; 
 int _INTC_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _intc_enable (struct irq_data*,int /*<<< orphan*/ ) ; 
 struct intc_desc_int* get_intc_desc (unsigned int) ; 
 struct intc_handle_int* intc_find_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  intc_get_prio_level (unsigned int) ; 
 int /*<<< orphan*/  intc_set_prio_level (unsigned int,unsigned int) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 

int intc_set_priority(unsigned int irq, unsigned int prio)
{
	struct intc_desc_int *d = get_intc_desc(irq);
	struct irq_data *data = irq_get_irq_data(irq);
	struct intc_handle_int *ihp;

	if (!intc_get_prio_level(irq) || prio <= 1)
		return -EINVAL;

	ihp = intc_find_irq(d->prio, d->nr_prio, irq);
	if (ihp) {
		if (prio >= (1 << _INTC_WIDTH(ihp->handle)))
			return -EINVAL;

		intc_set_prio_level(irq, prio);

		/*
		 * only set secondary masking method directly
		 * primary masking method is using intc_prio_level[irq]
		 * priority level will be set during next enable()
		 */
		if (_INTC_FN(ihp->handle) != REG_FN_ERR)
			_intc_enable(data, ihp->handle);
	}
	return 0;
}