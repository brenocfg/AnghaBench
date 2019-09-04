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
struct module {int /*<<< orphan*/  name; TYPE_1__ arch; } ;
struct mips_hi16 {int value; unsigned long* addr; struct mips_hi16* next; } ;
typedef  int Elf_Addr ;

/* Variables and functions */
 int ENOEXEC ; 
 int /*<<< orphan*/  free_relocation_chain (struct mips_hi16*) ; 
 int /*<<< orphan*/  kfree (struct mips_hi16*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_r_mips_lo16(struct module *me, u32 *location,
			     u32 base, Elf_Addr v, bool rela)
{
	unsigned long insnlo = base;
	struct mips_hi16 *l;
	Elf_Addr val, vallo;

	if (rela) {
		*location = (*location & 0xffff0000) | (v & 0xffff);
		return 0;
	}

	/* Sign extend the addend we extract from the lo insn.	*/
	vallo = ((insnlo & 0xffff) ^ 0x8000) - 0x8000;

	if (me->arch.r_mips_hi16_list != NULL) {
		l = me->arch.r_mips_hi16_list;
		while (l != NULL) {
			struct mips_hi16 *next;
			unsigned long insn;

			/*
			 * The value for the HI16 had best be the same.
			 */
			if (v != l->value)
				goto out_danger;

			/*
			 * Do the HI16 relocation.  Note that we actually don't
			 * need to know anything about the LO16 itself, except
			 * where to find the low 16 bits of the addend needed
			 * by the LO16.
			 */
			insn = *l->addr;
			val = ((insn & 0xffff) << 16) + vallo;
			val += v;

			/*
			 * Account for the sign extension that will happen in
			 * the low bits.
			 */
			val = ((val >> 16) + ((val & 0x8000) != 0)) & 0xffff;

			insn = (insn & ~0xffff) | val;
			*l->addr = insn;

			next = l->next;
			kfree(l);
			l = next;
		}

		me->arch.r_mips_hi16_list = NULL;
	}

	/*
	 * Ok, we're done with the HI16 relocs.	 Now deal with the LO16.
	 */
	val = v + vallo;
	insnlo = (insnlo & ~0xffff) | (val & 0xffff);
	*location = insnlo;

	return 0;

out_danger:
	free_relocation_chain(l);
	me->arch.r_mips_hi16_list = NULL;

	pr_err("module %s: dangerous R_MIPS_LO16 relocation\n", me->name);

	return -ENOEXEC;
}