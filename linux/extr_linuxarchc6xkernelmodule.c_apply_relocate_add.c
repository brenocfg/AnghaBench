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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct module {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int r_offset; int r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_6__ {size_t sh_info; int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_5__ {int st_value; } ;
typedef  TYPE_1__ Elf_Sym ;
typedef  void* Elf_Addr ;
typedef  TYPE_2__ Elf32_Shdr ;
typedef  TYPE_3__ Elf32_Rela ;
typedef  int Elf32_Addr ;

/* Variables and functions */
 int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOEXEC ; 
#define  R_C6000_ABS16 135 
#define  R_C6000_ABS32 134 
#define  R_C6000_ABS8 133 
#define  R_C6000_ABS_H16 132 
#define  R_C6000_ABS_L16 131 
#define  R_C6000_PCR_S10 130 
#define  R_C6000_PCR_S12 129 
#define  R_C6000_PCR_S21 128 
 int /*<<< orphan*/  fixup_pcr (int*,int,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

int apply_relocate_add(Elf32_Shdr *sechdrs,
		       const char *strtab,
		       unsigned int symindex,
		       unsigned int relsec,
		       struct module *me)
{
	Elf32_Rela *rel = (void *) sechdrs[relsec].sh_addr;
	Elf_Sym *sym;
	u32 *location, opcode;
	unsigned int i;
	Elf32_Addr v;
	Elf_Addr offset = 0;

	pr_debug("Applying relocate section %u to %u with offset 0x%x\n",
		 relsec, sechdrs[relsec].sh_info, offset);

	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rel); i++) {
		/* This is where to make the change */
		location = (void *)sechdrs[sechdrs[relsec].sh_info].sh_addr
			+ rel[i].r_offset - offset;

		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym = (Elf_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rel[i].r_info);

		/* this is the adjustment to be made */
		v = sym->st_value + rel[i].r_addend;

		switch (ELF32_R_TYPE(rel[i].r_info)) {
		case R_C6000_ABS32:
			pr_debug("RELA ABS32: [%p] = 0x%x\n", location, v);
			*location = v;
			break;
		case R_C6000_ABS16:
			pr_debug("RELA ABS16: [%p] = 0x%x\n", location, v);
			*(u16 *)location = v;
			break;
		case R_C6000_ABS8:
			pr_debug("RELA ABS8: [%p] = 0x%x\n", location, v);
			*(u8 *)location = v;
			break;
		case R_C6000_ABS_L16:
			opcode = *location;
			opcode &= ~0x7fff80;
			opcode |= ((v & 0xffff) << 7);
			pr_debug("RELA ABS_L16[%p] v[0x%x] opcode[0x%x]\n",
				 location, v, opcode);
			*location = opcode;
			break;
		case R_C6000_ABS_H16:
			opcode = *location;
			opcode &= ~0x7fff80;
			opcode |= ((v >> 9) & 0x7fff80);
			pr_debug("RELA ABS_H16[%p] v[0x%x] opcode[0x%x]\n",
				 location, v, opcode);
			*location = opcode;
			break;
		case R_C6000_PCR_S21:
			if (fixup_pcr(location, v, 21, 7))
				return -ENOEXEC;
			break;
		case R_C6000_PCR_S12:
			if (fixup_pcr(location, v, 12, 16))
				return -ENOEXEC;
			break;
		case R_C6000_PCR_S10:
			if (fixup_pcr(location, v, 10, 13))
				return -ENOEXEC;
			break;
		default:
			pr_err("module %s: Unknown RELA relocation: %u\n",
			       me->name, ELF32_R_TYPE(rel[i].r_info));
			return -ENOEXEC;
		}
	}

	return 0;
}