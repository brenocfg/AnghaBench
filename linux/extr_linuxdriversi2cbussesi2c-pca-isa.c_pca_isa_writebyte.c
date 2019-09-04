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
 scalar_t__ base ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void pca_isa_writebyte(void *pd, int reg, int val)
{
#ifdef DEBUG_IO
	static char *names[] = { "T/O", "DAT", "ADR", "CON" };
	printk(KERN_DEBUG "*** write %s at %#lx <= %#04x\n", names[reg],
	       base+reg, val);
#endif
	outb(val, base+reg);
}