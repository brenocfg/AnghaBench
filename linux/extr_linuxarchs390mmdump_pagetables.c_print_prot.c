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

/* Variables and functions */
 unsigned int _PAGE_INVALID ; 
 unsigned int _PAGE_NOEXEC ; 
 unsigned int _PAGE_PROTECT ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void print_prot(struct seq_file *m, unsigned int pr, int level)
{
	static const char * const level_name[] =
		{ "ASCE", "PGD", "PUD", "PMD", "PTE" };

	seq_printf(m, "%s ", level_name[level]);
	if (pr & _PAGE_INVALID) {
		seq_printf(m, "I\n");
		return;
	}
	seq_puts(m, (pr & _PAGE_PROTECT) ? "RO " : "RW ");
	seq_puts(m, (pr & _PAGE_NOEXEC) ? "NX\n" : "X\n");
}