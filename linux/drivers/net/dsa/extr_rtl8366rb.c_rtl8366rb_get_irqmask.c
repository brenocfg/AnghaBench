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
typedef  int u32 ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static u32 rtl8366rb_get_irqmask(struct irq_data *d)
{
	int line = irqd_to_hwirq(d);
	u32 val;

	/* For line interrupts we combine link down in bits
	 * 6..11 with link up in bits 0..5 into one interrupt.
	 */
	if (line < 12)
		val = BIT(line) | BIT(line + 6);
	else
		val = BIT(line);
	return val;
}