#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct module {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int r_offset; int r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_6__ {size_t sh_info; int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_5__ {int st_value; } ;
typedef  TYPE_1__ Elf32_Sym ;
typedef  TYPE_2__ Elf32_Shdr ;
typedef  TYPE_3__ Elf32_Rela ;

/* Variables and functions */
 int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_OR32_32 131 
#define  R_OR32_CONST 130 
#define  R_OR32_CONSTH 129 
#define  R_OR32_JUMPTARG 128 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

int apply_relocate_add(Elf32_Shdr *sechdrs,
		       const char *strtab,
		       unsigned int symindex,
		       unsigned int relsec,
		       struct module *me)
{
	unsigned int i;
	Elf32_Rela *rel = (void *)sechdrs[relsec].sh_addr;
	Elf32_Sym *sym;
	uint32_t *location;
	uint32_t value;

	pr_debug("Applying relocate section %u to %u\n", relsec,
		 sechdrs[relsec].sh_info);
	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rel); i++) {
		/* This is where to make the change */
		location = (void *)sechdrs[sechdrs[relsec].sh_info].sh_addr
			+ rel[i].r_offset;

		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rel[i].r_info);
		value = sym->st_value + rel[i].r_addend;

		switch (ELF32_R_TYPE(rel[i].r_info)) {
		case R_OR32_32:
			*location = value;
			break;
		case R_OR32_CONST:
			*((uint16_t *)location + 1) = value;
			break;
		case R_OR32_CONSTH:
			*((uint16_t *)location + 1) = value >> 16;
			break;
		case R_OR32_JUMPTARG:
			value -= (uint32_t)location;
			value >>= 2;
			value &= 0x03ffffff;
			value |= *location & 0xfc000000;
			*location = value;
			break;
		default:
			pr_err("module %s: Unknown relocation: %u\n",
			       me->name, ELF32_R_TYPE(rel[i].r_info));
			break;
		}
	}

	return 0;
}