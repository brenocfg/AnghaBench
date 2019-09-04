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
 int /*<<< orphan*/  CIE ; 
 int /*<<< orphan*/  IAR ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  xintc_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void intc_mask_ack(struct irq_data *d)
{
	unsigned long mask = 1 << d->hwirq;

	pr_debug("irq-xilinx: disable_and_ack: %ld\n", d->hwirq);
	xintc_write(CIE, mask);
	xintc_write(IAR, mask);
}