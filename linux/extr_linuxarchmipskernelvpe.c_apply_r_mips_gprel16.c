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
typedef  scalar_t__ Elf32_Addr ;

/* Variables and functions */
 int ENOEXEC ; 
 int gp_addr ; 
 int gp_offs ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int apply_r_mips_gprel16(struct module *me, uint32_t *location,
				Elf32_Addr v)
{
	int rel;

	if (!(*location & 0xffff)) {
		rel = (int)v - gp_addr;
	} else {
		/* .sbss + gp(relative) + offset */
		/* kludge! */
		rel =  (int)(short)((int)v + gp_offs +
				    (int)(short)(*location & 0xffff) - gp_addr);
	}

	if ((rel > 32768) || (rel < -32768)) {
		pr_debug("VPE loader: apply_r_mips_gprel16: relative address 0x%x out of range of gp register\n",
			 rel);
		return -ENOEXEC;
	}

	*location = (*location & 0xffff0000) | (rel & 0xffff);

	return 0;
}