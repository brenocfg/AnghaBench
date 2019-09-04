#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct elfhdr {int dummy; } ;
struct elf_phdr {scalar_t__ p_type; int /*<<< orphan*/  p_memsz; int /*<<< orphan*/  p_filesz; int /*<<< orphan*/  p_paddr; int /*<<< orphan*/  p_offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_notes_buf_size; int /*<<< orphan*/  cpu_notes_buf; } ;

/* Variables and functions */
 scalar_t__ PT_NOTE ; 
 TYPE_1__ fw_dump ; 

__attribute__((used)) static void fadump_update_elfcore_header(char *bufp)
{
	struct elfhdr *elf;
	struct elf_phdr *phdr;

	elf = (struct elfhdr *)bufp;
	bufp += sizeof(struct elfhdr);

	/* First note is a place holder for cpu notes info. */
	phdr = (struct elf_phdr *)bufp;

	if (phdr->p_type == PT_NOTE) {
		phdr->p_paddr = fw_dump.cpu_notes_buf;
		phdr->p_offset	= phdr->p_paddr;
		phdr->p_filesz	= fw_dump.cpu_notes_buf_size;
		phdr->p_memsz = fw_dump.cpu_notes_buf_size;
	}
	return;
}