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
struct seq_file {int dummy; } ;
struct partition_desc {int /*<<< orphan*/  chained_desc; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct irq_chip {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct partition_desc* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct irq_chip* irq_desc_get_chip (int /*<<< orphan*/ ) ; 
 struct irq_data* irq_desc_get_irq_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void partition_irq_print_chip(struct irq_data *d, struct seq_file *p)
{
	struct partition_desc *part = irq_data_get_irq_chip_data(d);
	struct irq_chip *chip = irq_desc_get_chip(part->chained_desc);
	struct irq_data *data = irq_desc_get_irq_data(part->chained_desc);

	seq_printf(p, " %5s-%lu", chip->name, data->hwirq);
}