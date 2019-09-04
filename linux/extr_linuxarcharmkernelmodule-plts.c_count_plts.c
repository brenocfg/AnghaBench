#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  r_info; } ;
struct TYPE_7__ {int /*<<< orphan*/  st_shndx; } ;
typedef  int /*<<< orphan*/  Elf32_Word ;
typedef  TYPE_1__ Elf32_Sym ;
typedef  TYPE_2__ Elf32_Rel ;
typedef  int /*<<< orphan*/  Elf32_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_ARM_CALL 132 
#define  R_ARM_JUMP24 131 
#define  R_ARM_PC24 130 
#define  R_ARM_THM_CALL 129 
#define  R_ARM_THM_JUMP24 128 
 int /*<<< orphan*/  duplicate_rel (int /*<<< orphan*/ ,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  is_zero_addend_relocation (int /*<<< orphan*/ ,TYPE_2__ const*) ; 

__attribute__((used)) static unsigned int count_plts(const Elf32_Sym *syms, Elf32_Addr base,
			       const Elf32_Rel *rel, int num, Elf32_Word dstidx)
{
	unsigned int ret = 0;
	const Elf32_Sym *s;
	int i;

	for (i = 0; i < num; i++) {
		switch (ELF32_R_TYPE(rel[i].r_info)) {
		case R_ARM_CALL:
		case R_ARM_PC24:
		case R_ARM_JUMP24:
		case R_ARM_THM_CALL:
		case R_ARM_THM_JUMP24:
			/*
			 * We only have to consider branch targets that resolve
			 * to symbols that are defined in a different section.
			 * This is not simply a heuristic, it is a fundamental
			 * limitation, since there is no guaranteed way to emit
			 * PLT entries sufficiently close to the branch if the
			 * section size exceeds the range of a branch
			 * instruction. So ignore relocations against defined
			 * symbols if they live in the same section as the
			 * relocation target.
			 */
			s = syms + ELF32_R_SYM(rel[i].r_info);
			if (s->st_shndx == dstidx)
				break;

			/*
			 * Jump relocations with non-zero addends against
			 * undefined symbols are supported by the ELF spec, but
			 * do not occur in practice (e.g., 'jump n bytes past
			 * the entry point of undefined function symbol f').
			 * So we need to support them, but there is no need to
			 * take them into consideration when trying to optimize
			 * this code. So let's only check for duplicates when
			 * the addend is zero. (Note that calls into the core
			 * module via init PLT entries could involve section
			 * relative symbol references with non-zero addends, for
			 * which we may end up emitting duplicates, but the init
			 * PLT is released along with the rest of the .init
			 * region as soon as module loading completes.)
			 */
			if (!is_zero_addend_relocation(base, rel + i) ||
			    !duplicate_rel(base, rel, i))
				ret++;
		}
	}
	return ret;
}