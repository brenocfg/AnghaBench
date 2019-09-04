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
 int inb (scalar_t__) ; 

__attribute__((used)) static int pca_isa_readbyte(void *pd, int reg)
{
	int res = inb(base+reg);
#ifdef DEBUG_IO
	{
		static char *names[] = { "STA", "DAT", "ADR", "CON" };
		printk(KERN_DEBUG "*** read  %s => %#04x\n", names[reg], res);
	}
#endif
	return res;
}