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
typedef  unsigned long uint32_t ;
struct module {int dummy; } ;
struct mips_hi16 {scalar_t__ value; unsigned long* addr; struct mips_hi16* next; } ;
typedef  scalar_t__ Elf32_Addr ;

/* Variables and functions */
 int ENOEXEC ; 
 int /*<<< orphan*/  kfree (struct mips_hi16*) ; 
 struct mips_hi16* mips_hi16_list ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int apply_r_mips_lo16(struct module *me, uint32_t *location,
			     Elf32_Addr v)
{
	unsigned long insnlo = *location;
	Elf32_Addr val, vallo;
	struct mips_hi16 *l, *next;

	/* Sign extend the addend we extract from the lo insn.	*/
	vallo = ((insnlo & 0xffff) ^ 0x8000) - 0x8000;

	if (mips_hi16_list != NULL) {

		l = mips_hi16_list;
		while (l != NULL) {
			unsigned long insn;

			/*
			 * The value for the HI16 had best be the same.
			 */
			if (v != l->value) {
				pr_debug("VPE loader: apply_r_mips_lo16/hi16: inconsistent value information\n");
				goto out_free;
			}

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

		mips_hi16_list = NULL;
	}

	/*
	 * Ok, we're done with the HI16 relocs.	 Now deal with the LO16.
	 */
	val = v + vallo;
	insnlo = (insnlo & ~0xffff) | (val & 0xffff);
	*location = insnlo;

	return 0;

out_free:
	while (l != NULL) {
		next = l->next;
		kfree(l);
		l = next;
	}
	mips_hi16_list = NULL;

	return -ENOEXEC;
}