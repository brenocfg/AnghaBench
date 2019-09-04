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
struct gpio_chip {unsigned int base; unsigned int ngpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  stmpe_dbg_show_one (struct seq_file*,struct gpio_chip*,unsigned int,unsigned int) ; 

__attribute__((used)) static void stmpe_dbg_show(struct seq_file *s, struct gpio_chip *gc)
{
	unsigned i;
	unsigned gpio = gc->base;

	for (i = 0; i < gc->ngpio; i++, gpio++) {
		stmpe_dbg_show_one(s, gc, i, gpio);
		seq_putc(s, '\n');
	}
}