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
typedef  int u32 ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int /*<<< orphan*/ ) ; 

void dump_backtrace_stm(u32 *stack, u32 instruction)
{
	char str[80], *p;
	unsigned int x;
	int reg;

	for (reg = 10, x = 0, p = str; reg >= 0; reg--) {
		if (instruction & BIT(reg)) {
			p += sprintf(p, " r%d:%08x", reg, *stack--);
			if (++x == 6) {
				x = 0;
				p = str;
				printk("%s\n", str);
			}
		}
	}
	if (p != str)
		printk("%s\n", str);
}