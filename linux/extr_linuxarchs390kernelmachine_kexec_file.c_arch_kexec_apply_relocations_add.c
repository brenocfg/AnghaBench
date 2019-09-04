#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u8 ;
typedef  unsigned long u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct purgatory_info {TYPE_2__* sechdrs; void* purgatory_buf; TYPE_1__* ehdr; } ;
struct TYPE_13__ {unsigned long r_offset; int /*<<< orphan*/  r_info; scalar_t__ r_addend; } ;
struct TYPE_12__ {int sh_offset; int sh_size; unsigned long sh_addr; } ;
struct TYPE_11__ {size_t st_shndx; unsigned long st_value; } ;
struct TYPE_10__ {scalar_t__ sh_addr; } ;
struct TYPE_9__ {size_t e_shnum; } ;
typedef  TYPE_3__ Elf_Sym ;
typedef  TYPE_4__ Elf_Shdr ;
typedef  TYPE_5__ Elf_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOEXEC ; 
#define  R_390_12 138 
#define  R_390_16 137 
#define  R_390_20 136 
#define  R_390_32 135 
#define  R_390_64 134 
#define  R_390_8 133 
#define  R_390_PC16 132 
#define  R_390_PC16DBL 131 
#define  R_390_PC32 130 
#define  R_390_PC32DBL 129 
#define  R_390_PC64 128 
 size_t SHN_ABS ; 
 size_t SHN_COMMON ; 
 size_t SHN_UNDEF ; 

int arch_kexec_apply_relocations_add(struct purgatory_info *pi,
				     Elf_Shdr *section,
				     const Elf_Shdr *relsec,
				     const Elf_Shdr *symtab)
{
	Elf_Rela *relas;
	int i;

	relas = (void *)pi->ehdr + relsec->sh_offset;

	for (i = 0; i < relsec->sh_size / sizeof(*relas); i++) {
		const Elf_Sym *sym;	/* symbol to relocate */
		unsigned long addr;	/* final location after relocation */
		unsigned long val;	/* relocated symbol value */
		void *loc;		/* tmp location to modify */

		sym = (void *)pi->ehdr + symtab->sh_offset;
		sym += ELF64_R_SYM(relas[i].r_info);

		if (sym->st_shndx == SHN_UNDEF)
			return -ENOEXEC;

		if (sym->st_shndx == SHN_COMMON)
			return -ENOEXEC;

		if (sym->st_shndx >= pi->ehdr->e_shnum &&
		    sym->st_shndx != SHN_ABS)
			return -ENOEXEC;

		loc = pi->purgatory_buf;
		loc += section->sh_offset;
		loc += relas[i].r_offset;

		val = sym->st_value;
		if (sym->st_shndx != SHN_ABS)
			val += pi->sechdrs[sym->st_shndx].sh_addr;
		val += relas[i].r_addend;

		addr = section->sh_addr + relas[i].r_offset;

		switch (ELF64_R_TYPE(relas[i].r_info)) {
		case R_390_8:		/* Direct 8 bit.   */
			*(u8 *)loc = val;
			break;
		case R_390_12:		/* Direct 12 bit.  */
			*(u16 *)loc &= 0xf000;
			*(u16 *)loc |= val & 0xfff;
			break;
		case R_390_16:		/* Direct 16 bit.  */
			*(u16 *)loc = val;
			break;
		case R_390_20:		/* Direct 20 bit.  */
			*(u32 *)loc &= 0xf00000ff;
			*(u32 *)loc |= (val & 0xfff) << 16;	/* DL */
			*(u32 *)loc |= (val & 0xff000) >> 4;	/* DH */
			break;
		case R_390_32:		/* Direct 32 bit.  */
			*(u32 *)loc = val;
			break;
		case R_390_64:		/* Direct 64 bit.  */
			*(u64 *)loc = val;
			break;
		case R_390_PC16:	/* PC relative 16 bit.	*/
			*(u16 *)loc = (val - addr);
			break;
		case R_390_PC16DBL:	/* PC relative 16 bit shifted by 1.  */
			*(u16 *)loc = (val - addr) >> 1;
			break;
		case R_390_PC32DBL:	/* PC relative 32 bit shifted by 1.  */
			*(u32 *)loc = (val - addr) >> 1;
			break;
		case R_390_PC32:	/* PC relative 32 bit.	*/
			*(u32 *)loc = (val - addr);
			break;
		case R_390_PC64:	/* PC relative 64 bit.	*/
			*(u64 *)loc = (val - addr);
			break;
		default:
			break;
		}
	}
	return 0;
}