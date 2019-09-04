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
struct kimage {int dummy; } ;
struct kexec_buf {int top_down; size_t bufsz; size_t memsz; unsigned long mem; scalar_t__ buf_min; int /*<<< orphan*/  buf_align; void* buffer; int /*<<< orphan*/  buf_max; struct kimage* image; } ;
struct elfhdr {size_t e_phnum; unsigned long e_entry; } ;
struct elf_phdr {scalar_t__ p_type; size_t p_filesz; size_t p_memsz; int p_offset; scalar_t__ p_paddr; int /*<<< orphan*/  p_align; } ;
struct elf_info {scalar_t__ buffer; struct elf_phdr* proghdrs; } ;

/* Variables and functions */
 scalar_t__ PT_LOAD ; 
 unsigned long UINT_MAX ; 
 int kexec_add_buffer (struct kexec_buf*) ; 
 int /*<<< orphan*/  ppc64_rma_size ; 

__attribute__((used)) static int elf_exec_load(struct kimage *image, struct elfhdr *ehdr,
			 struct elf_info *elf_info,
			 unsigned long *lowest_load_addr)
{
	unsigned long base = 0, lowest_addr = UINT_MAX;
	int ret;
	size_t i;
	struct kexec_buf kbuf = { .image = image, .buf_max = ppc64_rma_size,
				  .top_down = false };

	/* Read in the PT_LOAD segments. */
	for (i = 0; i < ehdr->e_phnum; i++) {
		unsigned long load_addr;
		size_t size;
		const struct elf_phdr *phdr;

		phdr = &elf_info->proghdrs[i];
		if (phdr->p_type != PT_LOAD)
			continue;

		size = phdr->p_filesz;
		if (size > phdr->p_memsz)
			size = phdr->p_memsz;

		kbuf.buffer = (void *) elf_info->buffer + phdr->p_offset;
		kbuf.bufsz = size;
		kbuf.memsz = phdr->p_memsz;
		kbuf.buf_align = phdr->p_align;
		kbuf.buf_min = phdr->p_paddr + base;
		ret = kexec_add_buffer(&kbuf);
		if (ret)
			goto out;
		load_addr = kbuf.mem;

		if (load_addr < lowest_addr)
			lowest_addr = load_addr;
	}

	/* Update entry point to reflect new load address. */
	ehdr->e_entry += base;

	*lowest_load_addr = lowest_addr;
	ret = 0;
 out:
	return ret;
}