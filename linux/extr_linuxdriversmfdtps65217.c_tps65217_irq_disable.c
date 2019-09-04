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
typedef  int u8 ;
struct tps65217 {int irq_mask; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int TPS65217_INT_SHIFT ; 
 struct tps65217* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void tps65217_irq_disable(struct irq_data *data)
{
	struct tps65217 *tps = irq_data_get_irq_chip_data(data);
	u8 mask = BIT(data->hwirq) << TPS65217_INT_SHIFT;

	tps->irq_mask |= mask;
}