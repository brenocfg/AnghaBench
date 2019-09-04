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
struct module {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int r_offset; int r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_6__ {int sh_addr; size_t sh_info; int sh_size; } ;
struct TYPE_5__ {int st_value; } ;
typedef  TYPE_1__ Elf32_Sym ;
typedef  int Elf32_Sword ;
typedef  TYPE_2__ Elf32_Shdr ;
typedef  TYPE_3__ Elf32_Rela ;

/* Variables and functions */
 int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOEXEC ; 
#define  R_H8_DIR24A8 133 
#define  R_H8_DIR24R8 132 
#define  R_H8_DIR32 131 
#define  R_H8_DIR32A16 130 
#define  R_H8_PCREL16 129 
#define  R_H8_PCREL8 128 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

int apply_relocate_add(Elf32_Shdr *sechdrs,
		       const char *strtab,
		       unsigned int symindex,
		       unsigned int relsec,
		       struct module *me)
{
	unsigned int i;
	Elf32_Rela *rela = (void *)sechdrs[relsec].sh_addr;

	pr_debug("Applying relocate section %u to %u\n", relsec,
	       sechdrs[relsec].sh_info);
	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rela); i++) {
		/* This is where to make the change */
		uint32_t *loc =
			(uint32_t *)(sechdrs[sechdrs[relsec].sh_info].sh_addr
					     + rela[i].r_offset);
		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		Elf32_Sym *sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rela[i].r_info);
		uint32_t v = sym->st_value + rela[i].r_addend;

		switch (ELF32_R_TYPE(rela[i].r_info)) {
		case R_H8_DIR24R8:
			loc = (uint32_t *)((uint32_t)loc - 1);
			*loc = (*loc & 0xff000000) | ((*loc & 0xffffff) + v);
			break;
		case R_H8_DIR24A8:
			if (ELF32_R_SYM(rela[i].r_info))
				*loc += v;
			break;
		case R_H8_DIR32:
		case R_H8_DIR32A16:
			*loc += v;
			break;
		case R_H8_PCREL16:
			v -= (unsigned long)loc + 2;
			if ((Elf32_Sword)v > 0x7fff ||
			    (Elf32_Sword)v < -(Elf32_Sword)0x8000)
				goto overflow;
			else
				*(unsigned short *)loc = v;
			break;
		case R_H8_PCREL8:
			v -= (unsigned long)loc + 1;
			if ((Elf32_Sword)v > 0x7f ||
			    (Elf32_Sword)v < -(Elf32_Sword)0x80)
				goto overflow;
			else
				*(unsigned char *)loc = v;
			break;
		default:
			pr_err("module %s: Unknown relocation: %u\n",
			       me->name, ELF32_R_TYPE(rela[i].r_info));
			return -ENOEXEC;
		}
	}
	return 0;
 overflow:
	pr_err("module %s: relocation offset overflow: %08x\n",
	       me->name, rela[i].r_offset);
	return -ENOEXEC;
}