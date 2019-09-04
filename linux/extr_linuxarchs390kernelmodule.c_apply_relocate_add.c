#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct TYPE_3__ {size_t sh_info; int sh_size; scalar_t__ sh_addr; } ;
typedef  int /*<<< orphan*/  Elf_Sym ;
typedef  TYPE_1__ Elf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Rela ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (char*,unsigned int,size_t) ; 
 int apply_rela (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,char const*,struct module*) ; 

int apply_relocate_add(Elf_Shdr *sechdrs, const char *strtab,
		       unsigned int symindex, unsigned int relsec,
		       struct module *me)
{
	Elf_Addr base;
	Elf_Sym *symtab;
	Elf_Rela *rela;
	unsigned long i, n;
	int rc;

	DEBUGP("Applying relocate section %u to %u\n",
	       relsec, sechdrs[relsec].sh_info);
	base = sechdrs[sechdrs[relsec].sh_info].sh_addr;
	symtab = (Elf_Sym *) sechdrs[symindex].sh_addr;
	rela = (Elf_Rela *) sechdrs[relsec].sh_addr;
	n = sechdrs[relsec].sh_size / sizeof(Elf_Rela);

	for (i = 0; i < n; i++, rela++) {
		rc = apply_rela(rela, base, symtab, strtab, me);
		if (rc)
			return rc;
	}
	return 0;
}