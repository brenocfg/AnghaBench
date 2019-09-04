#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_5__ {scalar_t__ st_shndx; int st_name; } ;
typedef  TYPE_1__ Elf64_Sym ;
typedef  TYPE_2__ Elf64_Shdr ;

/* Variables and functions */
 scalar_t__ SHN_ABS ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static Elf64_Sym *find_dot_toc(Elf64_Shdr *sechdrs,
			       const char *strtab,
			       unsigned int symindex)
{
	unsigned int i, numsyms;
	Elf64_Sym *syms;

	syms = (Elf64_Sym *)sechdrs[symindex].sh_addr;
	numsyms = sechdrs[symindex].sh_size / sizeof(Elf64_Sym);

	for (i = 1; i < numsyms; i++) {
		if (syms[i].st_shndx == SHN_ABS
		    && strcmp(strtab + syms[i].st_name, "TOC.") == 0)
			return &syms[i];
	}
	return NULL;
}