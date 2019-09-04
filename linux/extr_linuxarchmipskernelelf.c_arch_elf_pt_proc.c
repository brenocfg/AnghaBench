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
typedef  int u32 ;
struct mips_elf_abiflags_v0 {void* fp_abi; } ;
struct file {int dummy; } ;
struct elf64_phdr {scalar_t__ p_type; int p_filesz; int /*<<< orphan*/  p_offset; } ;
struct elf64_hdr {int e_flags; } ;
struct elf32_phdr {scalar_t__ p_type; int p_filesz; int /*<<< orphan*/  p_offset; } ;
struct elf32_hdr {scalar_t__* e_ident; int e_flags; } ;
struct arch_elf_state {void* fp_abi; void* interp_fp_abi; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  abiflags ;

/* Variables and functions */
 int EF_MIPS_FP64 ; 
 int EINVAL ; 
 int EIO ; 
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS32 ; 
 void* MIPS_ABI_FP_OLD_64 ; 
 scalar_t__ PT_MIPS_ABIFLAGS ; 
 int kernel_read (struct file*,struct mips_elf_abiflags_v0*,int,int /*<<< orphan*/ *) ; 

int arch_elf_pt_proc(void *_ehdr, void *_phdr, struct file *elf,
		     bool is_interp, struct arch_elf_state *state)
{
	union {
		struct elf32_hdr e32;
		struct elf64_hdr e64;
	} *ehdr = _ehdr;
	struct elf32_phdr *phdr32 = _phdr;
	struct elf64_phdr *phdr64 = _phdr;
	struct mips_elf_abiflags_v0 abiflags;
	bool elf32;
	u32 flags;
	int ret;
	loff_t pos;

	elf32 = ehdr->e32.e_ident[EI_CLASS] == ELFCLASS32;
	flags = elf32 ? ehdr->e32.e_flags : ehdr->e64.e_flags;

	/* Let's see if this is an O32 ELF */
	if (elf32) {
		if (flags & EF_MIPS_FP64) {
			/*
			 * Set MIPS_ABI_FP_OLD_64 for EF_MIPS_FP64. We will override it
			 * later if needed
			 */
			if (is_interp)
				state->interp_fp_abi = MIPS_ABI_FP_OLD_64;
			else
				state->fp_abi = MIPS_ABI_FP_OLD_64;
		}
		if (phdr32->p_type != PT_MIPS_ABIFLAGS)
			return 0;

		if (phdr32->p_filesz < sizeof(abiflags))
			return -EINVAL;
		pos = phdr32->p_offset;
	} else {
		if (phdr64->p_type != PT_MIPS_ABIFLAGS)
			return 0;
		if (phdr64->p_filesz < sizeof(abiflags))
			return -EINVAL;
		pos = phdr64->p_offset;
	}

	ret = kernel_read(elf, &abiflags, sizeof(abiflags), &pos);
	if (ret < 0)
		return ret;
	if (ret != sizeof(abiflags))
		return -EIO;

	/* Record the required FP ABIs for use by mips_check_elf */
	if (is_interp)
		state->interp_fp_abi = abiflags.fp_abi;
	else
		state->fp_abi = abiflags.fp_abi;

	return 0;
}