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
typedef  int u16 ;
struct ts4800_irq_data {scalar_t__ base; } ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 scalar_t__ IRQ_MASK ; 
 struct ts4800_irq_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void ts4800_irq_mask(struct irq_data *d)
{
	struct ts4800_irq_data *data = irq_data_get_irq_chip_data(d);
	u16 reg = readw(data->base + IRQ_MASK);
	u16 mask = 1 << d->hwirq;

	writew(reg | mask, data->base + IRQ_MASK);
}