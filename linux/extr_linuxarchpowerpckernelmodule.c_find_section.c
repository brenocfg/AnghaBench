#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t e_shstrndx; unsigned int e_shnum; } ;
struct TYPE_6__ {int sh_offset; int sh_name; } ;
typedef  TYPE_1__ Elf_Shdr ;
typedef  TYPE_2__ Elf_Ehdr ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static const Elf_Shdr *find_section(const Elf_Ehdr *hdr,
				    const Elf_Shdr *sechdrs,
				    const char *name)
{
	char *secstrings;
	unsigned int i;

	secstrings = (char *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;
	for (i = 1; i < hdr->e_shnum; i++)
		if (strcmp(secstrings+sechdrs[i].sh_name, name) == 0)
			return &sechdrs[i];
	return NULL;
}