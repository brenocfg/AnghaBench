#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {struct mips_hi16* r_mips_hi16_list; } ;
struct module {TYPE_1__ arch; } ;
struct mips_hi16 {struct mips_hi16* next; scalar_t__ value; scalar_t__* addr; } ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mips_hi16* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_r_mips_hi16(struct module *me, u32 *location,
			     u32 base, Elf_Addr v, bool rela)
{
	struct mips_hi16 *n;

	if (rela) {
		*location = (*location & 0xffff0000) |
			    ((((long long) v + 0x8000LL) >> 16) & 0xffff);
		return 0;
	}

	/*
	 * We cannot relocate this one now because we don't know the value of
	 * the carry we need to add.  Save the information, and let LO16 do the
	 * actual relocation.
	 */
	n = kmalloc(sizeof *n, GFP_KERNEL);
	if (!n)
		return -ENOMEM;

	n->addr = (Elf_Addr *)location;
	n->value = v;
	n->next = me->arch.r_mips_hi16_list;
	me->arch.r_mips_hi16_list = n;

	return 0;
}