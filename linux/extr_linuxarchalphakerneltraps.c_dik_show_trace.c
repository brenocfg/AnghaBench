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

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void
dik_show_trace(unsigned long *sp)
{
	long i = 0;
	printk("Trace:\n");
	while (0x1ff8 & (unsigned long) sp) {
		extern char _stext[], _etext[];
		unsigned long tmp = *sp;
		sp++;
		if (tmp < (unsigned long) &_stext)
			continue;
		if (tmp >= (unsigned long) &_etext)
			continue;
		printk("[<%lx>] %pSR\n", tmp, (void *)tmp);
		if (i > 40) {
			printk(" ...");
			break;
		}
	}
	printk("\n");
}