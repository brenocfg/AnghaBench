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
struct stmfx {int /*<<< orphan*/  irq_src; } ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 struct stmfx* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void stmfx_irq_unmask(struct irq_data *data)
{
	struct stmfx *stmfx = irq_data_get_irq_chip_data(data);

	stmfx->irq_src |= BIT(data->hwirq % 8);
}