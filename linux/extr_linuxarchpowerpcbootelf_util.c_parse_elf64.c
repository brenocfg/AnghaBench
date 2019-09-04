#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct elf_info {unsigned long loadsize; unsigned long memsize; unsigned long elfoffset; } ;
struct TYPE_4__ {scalar_t__* e_ident; scalar_t__ e_type; scalar_t__ e_machine; scalar_t__ e_phnum; scalar_t__ e_phoff; } ;
struct TYPE_3__ {scalar_t__ p_type; scalar_t__ p_offset; scalar_t__ p_memsz; scalar_t__ p_filesz; } ;
typedef  TYPE_1__ Elf64_Phdr ;
typedef  TYPE_2__ Elf64_Ehdr ;

/* Variables and functions */
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_MAG0 ; 
 size_t EI_MAG1 ; 
 size_t EI_MAG2 ; 
 size_t EI_MAG3 ; 
 scalar_t__ ELFCLASS64 ; 
 scalar_t__ ELFDATA2LSB ; 
 scalar_t__ ELFMAG0 ; 
 scalar_t__ ELFMAG1 ; 
 scalar_t__ ELFMAG2 ; 
 scalar_t__ ELFMAG3 ; 
 scalar_t__ EM_PPC64 ; 
 scalar_t__ ET_DYN ; 
 scalar_t__ ET_EXEC ; 
 scalar_t__ PT_LOAD ; 

int parse_elf64(void *hdr, struct elf_info *info)
{
	Elf64_Ehdr *elf64 = hdr;
	Elf64_Phdr *elf64ph;
	unsigned int i;

	if (!(elf64->e_ident[EI_MAG0]  == ELFMAG0	&&
	      elf64->e_ident[EI_MAG1]  == ELFMAG1	&&
	      elf64->e_ident[EI_MAG2]  == ELFMAG2	&&
	      elf64->e_ident[EI_MAG3]  == ELFMAG3	&&
	      elf64->e_ident[EI_CLASS] == ELFCLASS64	&&
#ifdef __LITTLE_ENDIAN__
	      elf64->e_ident[EI_DATA]  == ELFDATA2LSB	&&
#else
	      elf64->e_ident[EI_DATA]  == ELFDATA2MSB	&&
#endif
	      (elf64->e_type            == ET_EXEC ||
	       elf64->e_type            == ET_DYN)	&&
	      elf64->e_machine         == EM_PPC64))
		return 0;

	elf64ph = (Elf64_Phdr *)((unsigned long)elf64 +
				 (unsigned long)elf64->e_phoff);
	for (i = 0; i < (unsigned int)elf64->e_phnum; i++, elf64ph++)
		if (elf64ph->p_type == PT_LOAD)
			break;
	if (i >= (unsigned int)elf64->e_phnum)
		return 0;

	info->loadsize = (unsigned long)elf64ph->p_filesz;
	info->memsize = (unsigned long)elf64ph->p_memsz;
	info->elfoffset = (unsigned long)elf64ph->p_offset;

	return 1;
}