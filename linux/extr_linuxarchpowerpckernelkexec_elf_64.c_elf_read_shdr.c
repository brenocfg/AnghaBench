#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct elfhdr {int e_shoff; } ;
struct elf_shdr {void* sh_entsize; void* sh_addralign; void* sh_size; void* sh_flags; void* sh_info; void* sh_link; void* sh_offset; void* sh_addr; void* sh_type; void* sh_name; } ;
struct elf_info {struct elfhdr* ehdr; struct elf_shdr* sechdrs; } ;

/* Variables and functions */
 int ENOEXEC ; 
 void* elf32_to_cpu (struct elfhdr const*,void*) ; 
 void* elf_addr_to_cpu (struct elfhdr const*,void*) ; 
 scalar_t__ elf_is_shdr_sane (struct elf_shdr*,size_t) ; 

__attribute__((used)) static int elf_read_shdr(const char *buf, size_t len, struct elf_info *elf_info,
			 int idx)
{
	struct elf_shdr *shdr = &elf_info->sechdrs[idx];
	const struct elfhdr *ehdr = elf_info->ehdr;
	const char *sbuf;
	struct elf_shdr *buf_shdr;

	sbuf = buf + ehdr->e_shoff + idx * sizeof(*buf_shdr);
	buf_shdr = (struct elf_shdr *) sbuf;

	shdr->sh_name      = elf32_to_cpu(ehdr, buf_shdr->sh_name);
	shdr->sh_type      = elf32_to_cpu(ehdr, buf_shdr->sh_type);
	shdr->sh_addr      = elf_addr_to_cpu(ehdr, buf_shdr->sh_addr);
	shdr->sh_offset    = elf_addr_to_cpu(ehdr, buf_shdr->sh_offset);
	shdr->sh_link      = elf32_to_cpu(ehdr, buf_shdr->sh_link);
	shdr->sh_info      = elf32_to_cpu(ehdr, buf_shdr->sh_info);

	/*
	 * The following fields have a type equivalent to Elf_Addr
	 * both in 32 bit and 64 bit ELF.
	 */
	shdr->sh_flags     = elf_addr_to_cpu(ehdr, buf_shdr->sh_flags);
	shdr->sh_size      = elf_addr_to_cpu(ehdr, buf_shdr->sh_size);
	shdr->sh_addralign = elf_addr_to_cpu(ehdr, buf_shdr->sh_addralign);
	shdr->sh_entsize   = elf_addr_to_cpu(ehdr, buf_shdr->sh_entsize);

	return elf_is_shdr_sane(shdr, len) ? 0 : -ENOEXEC;
}