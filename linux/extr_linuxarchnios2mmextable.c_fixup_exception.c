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
struct pt_regs {int /*<<< orphan*/  ea; } ;
struct exception_table_entry {int /*<<< orphan*/  fixup; } ;

/* Variables and functions */
 struct exception_table_entry* search_exception_tables (int /*<<< orphan*/ ) ; 

int fixup_exception(struct pt_regs *regs)
{
	const struct exception_table_entry *fixup;

	fixup = search_exception_tables(regs->ea);
	if (fixup) {
		regs->ea = fixup->fixup;
		return 1;
	}

	return 0;
}