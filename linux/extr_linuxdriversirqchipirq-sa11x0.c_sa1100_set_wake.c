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
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int sa11x0_sc_set_wake (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int sa1100_set_wake(struct irq_data *d, unsigned int on)
{
	return sa11x0_sc_set_wake(d->hwirq, on);
}