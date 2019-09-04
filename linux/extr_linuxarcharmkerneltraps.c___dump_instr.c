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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned int get_user (unsigned int,int /*<<< orphan*/ *) ; 
 unsigned long instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  printk (char*,char const*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int thumb_mode (struct pt_regs*) ; 

__attribute__((used)) static void __dump_instr(const char *lvl, struct pt_regs *regs)
{
	unsigned long addr = instruction_pointer(regs);
	const int thumb = thumb_mode(regs);
	const int width = thumb ? 4 : 8;
	char str[sizeof("00000000 ") * 5 + 2 + 1], *p = str;
	int i;

	/*
	 * Note that we now dump the code first, just in case the backtrace
	 * kills us.
	 */

	for (i = -4; i < 1 + !!thumb; i++) {
		unsigned int val, bad;

		if (thumb)
			bad = get_user(val, &((u16 *)addr)[i]);
		else
			bad = get_user(val, &((u32 *)addr)[i]);

		if (!bad)
			p += sprintf(p, i == 0 ? "(%0*x) " : "%0*x ",
					width, val);
		else {
			p += sprintf(p, "bad PC value");
			break;
		}
	}
	printk("%sCode: %s\n", lvl, str);
}