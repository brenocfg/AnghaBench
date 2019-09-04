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
struct irqaction {int /*<<< orphan*/  name; struct irqaction* next; } ;
struct irq_desc {struct irqaction* action; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ irq_first ; 
 struct irq_desc* irq_to_desc (scalar_t__) ; 
 int num_interrupt_lines ; 
 int /*<<< orphan*/ * num_interrupts ; 
 int /*<<< orphan*/ * num_wake_interrupts ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int ab8500_interrupts_show(struct seq_file *s, void *p)
{
	int line;

	seq_puts(s, "name: number:  number of: wake:\n");

	for (line = 0; line < num_interrupt_lines; line++) {
		struct irq_desc *desc = irq_to_desc(line + irq_first);

		seq_printf(s, "%3i:  %6i %4i",
			   line,
			   num_interrupts[line],
			   num_wake_interrupts[line]);

		if (desc && desc->name)
			seq_printf(s, "-%-8s", desc->name);
		if (desc && desc->action) {
			struct irqaction *action = desc->action;

			seq_printf(s, "  %s", action->name);
			while ((action = action->next) != NULL)
				seq_printf(s, ", %s", action->name);
		}
		seq_putc(s, '\n');
	}

	return 0;
}