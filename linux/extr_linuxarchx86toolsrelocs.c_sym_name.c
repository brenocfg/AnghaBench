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
struct TYPE_3__ {int st_name; int /*<<< orphan*/  st_shndx; } ;
typedef  TYPE_1__ Elf_Sym ;

/* Variables and functions */
 char* sec_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *sym_name(const char *sym_strtab, Elf_Sym *sym)
{
	const char *name;
	name = "<noname>";
	if (sym->st_name) {
		name = sym_strtab + sym->st_name;
	}
	else {
		name = sec_name(sym->st_shndx);
	}
	return name;
}