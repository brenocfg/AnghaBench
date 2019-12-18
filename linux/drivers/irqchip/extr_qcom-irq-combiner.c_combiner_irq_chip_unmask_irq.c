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
struct combiner_reg {int /*<<< orphan*/  enabled; } ;
struct combiner {struct combiner_reg* regs; } ;

/* Variables and functions */
 int REG_SIZE ; 
 struct combiner* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void combiner_irq_chip_unmask_irq(struct irq_data *data)
{
	struct combiner *combiner = irq_data_get_irq_chip_data(data);
	struct combiner_reg *reg = combiner->regs + data->hwirq / REG_SIZE;

	set_bit(data->hwirq % REG_SIZE, &reg->enabled);
}