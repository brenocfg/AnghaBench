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
struct elf_phdr {void* p_align; void* p_memsz; void* p_filesz; void* p_flags; void* p_vaddr; void* p_paddr; void* p_offset; void* p_type; } ;
struct elf_info {TYPE_1__* ehdr; int /*<<< orphan*/ * proghdrs; } ;
struct TYPE_3__ {int e_phoff; } ;

/* Variables and functions */
 int ENOEXEC ; 
 void* elf32_to_cpu (TYPE_1__*,void*) ; 
 void* elf_addr_to_cpu (TYPE_1__*,void*) ; 
 scalar_t__ elf_is_phdr_sane (struct elf_phdr*,size_t) ; 

__attribute__((used)) static int elf_read_phdr(const char *buf, size_t len, struct elf_info *elf_info,
			 int idx)
{
	/* Override the const in proghdrs, we are the ones doing the loading. */
	struct elf_phdr *phdr = (struct elf_phdr *) &elf_info->proghdrs[idx];
	const char *pbuf;
	struct elf_phdr *buf_phdr;

	pbuf = buf + elf_info->ehdr->e_phoff + (idx * sizeof(*buf_phdr));
	buf_phdr = (struct elf_phdr *) pbuf;

	phdr->p_type   = elf32_to_cpu(elf_info->ehdr, buf_phdr->p_type);
	phdr->p_offset = elf_addr_to_cpu(elf_info->ehdr, buf_phdr->p_offset);
	phdr->p_paddr  = elf_addr_to_cpu(elf_info->ehdr, buf_phdr->p_paddr);
	phdr->p_vaddr  = elf_addr_to_cpu(elf_info->ehdr, buf_phdr->p_vaddr);
	phdr->p_flags  = elf32_to_cpu(elf_info->ehdr, buf_phdr->p_flags);

	/*
	 * The following fields have a type equivalent to Elf_Addr
	 * both in 32 bit and 64 bit ELF.
	 */
	phdr->p_filesz = elf_addr_to_cpu(elf_info->ehdr, buf_phdr->p_filesz);
	phdr->p_memsz  = elf_addr_to_cpu(elf_info->ehdr, buf_phdr->p_memsz);
	phdr->p_align  = elf_addr_to_cpu(elf_info->ehdr, buf_phdr->p_align);

	return elf_is_phdr_sane(phdr, len) ? 0 : -ENOEXEC;
}