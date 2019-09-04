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
struct pt_regs {int pc; } ;

/* Variables and functions */
 scalar_t__ __get_user (unsigned short,unsigned short*) ; 
 int /*<<< orphan*/  print_sh_insn (unsigned long,unsigned short) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

void show_code(struct pt_regs *regs)
{
	unsigned short *pc = (unsigned short *)regs->pc;
	long i;

	if (regs->pc & 0x1)
		return;

	printk("Code:\n");

	for (i = -3 ; i < 6 ; i++) {
		unsigned short insn;

		if (__get_user(insn, pc + i)) {
			printk(" (Bad address in pc)\n");
			break;
		}

		printk("%s%08lx:  ", (i ? "  ": "->"), (unsigned long)(pc + i));
		print_sh_insn((unsigned long)(pc + i), insn);
		printk("\n");
	}

	printk("\n");
}