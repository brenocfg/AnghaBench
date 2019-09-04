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
typedef  int uint32_t ;
struct module {int dummy; } ;
typedef  int Elf32_Addr ;

/* Variables and functions */
 int ENOEXEC ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int apply_r_mips_26(struct module *me, uint32_t *location,
			   Elf32_Addr v)
{
	if (v % 4) {
		pr_debug("VPE loader: apply_r_mips_26: unaligned relocation\n");
		return -ENOEXEC;
	}

/*
 * Not desperately convinced this is a good check of an overflow condition
 * anyway. But it gets in the way of handling undefined weak symbols which
 * we want to set to zero.
 * if ((v & 0xf0000000) != (((unsigned long)location + 4) & 0xf0000000)) {
 * printk(KERN_ERR
 * "module %s: relocation overflow\n",
 * me->name);
 * return -ENOEXEC;
 * }
 */

	*location = (*location & ~0x03ffffff) |
		((*location + (v >> 2)) & 0x03ffffff);
	return 0;
}