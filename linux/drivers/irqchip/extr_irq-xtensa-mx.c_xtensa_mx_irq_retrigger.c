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
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (unsigned int) ; 
 unsigned int XCHAL_INTTYPE_MASK_SOFTWARE ; 
 int /*<<< orphan*/  intset ; 
 int /*<<< orphan*/  xtensa_set_sr (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xtensa_mx_irq_retrigger(struct irq_data *d)
{
	unsigned int mask = 1u << d->hwirq;

	if (WARN_ON(mask & ~XCHAL_INTTYPE_MASK_SOFTWARE))
		return 0;
	xtensa_set_sr(mask, intset);
	return 1;
}