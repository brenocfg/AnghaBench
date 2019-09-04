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
struct module {int /*<<< orphan*/  name; } ;
typedef  int s32 ;
typedef  int ptrdiff_t ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,long long,int*) ; 

__attribute__((used)) static int apply_r_riscv_pcrel_hi20_rela(struct module *me, u32 *location,
					 Elf_Addr v)
{
	ptrdiff_t offset = (void *)v - (void *)location;
	s32 hi20;

	if (offset != (s32)offset) {
		pr_err(
		  "%s: target %016llx can not be addressed by the 32-bit offset from PC = %p\n",
		  me->name, (long long)v, location);
		return -EINVAL;
	}

	hi20 = (offset + 0x800) & 0xfffff000;
	*location = (*location & 0xfff) | hi20;
	return 0;
}