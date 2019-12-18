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
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAR ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  xintc_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void intc_ack(struct irq_data *d)
{
	pr_debug("irq-xilinx: ack: %ld\n", d->hwirq);
	xintc_write(IAR, 1 << d->hwirq);
}