#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vpe {int /*<<< orphan*/ * shared_ptr; scalar_t__ __start; } ;
struct module {int dummy; } ;
struct TYPE_5__ {int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_4__ {int st_name; scalar_t__ st_value; } ;
typedef  TYPE_1__ Elf_Sym ;
typedef  TYPE_2__ Elf_Shdr ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int find_vpe_symbols(struct vpe *v, Elf_Shdr *sechdrs,
				      unsigned int symindex, const char *strtab,
				      struct module *mod)
{
	Elf_Sym *sym = (void *)sechdrs[symindex].sh_addr;
	unsigned int i, n = sechdrs[symindex].sh_size / sizeof(Elf_Sym);

	for (i = 1; i < n; i++) {
		if (strcmp(strtab + sym[i].st_name, "__start") == 0)
			v->__start = sym[i].st_value;

		if (strcmp(strtab + sym[i].st_name, "vpe_shared") == 0)
			v->shared_ptr = (void *)sym[i].st_value;
	}

	if ((v->__start == 0) || (v->shared_ptr == NULL))
		return -1;

	return 0;
}