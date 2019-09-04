#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long pc; unsigned long range; } ;
struct TYPE_4__ {unsigned long pc; unsigned long range; } ;
struct unwind_table {TYPE_1__ init; TYPE_2__ core; struct unwind_table* link; } ;

/* Variables and functions */
 struct unwind_table root_table ; 

__attribute__((used)) static struct unwind_table *find_table(unsigned long pc)
{
	struct unwind_table *table;

	for (table = &root_table; table; table = table->link)
		if ((pc >= table->core.pc
		     && pc < table->core.pc + table->core.range)
		    || (pc >= table->init.pc
			&& pc < table->init.pc + table->init.range))
			break;

	return table;
}