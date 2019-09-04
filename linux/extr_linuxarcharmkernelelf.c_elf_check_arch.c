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
struct elf32_hdr {scalar_t__ e_machine; int e_entry; unsigned int e_flags; } ;

/* Variables and functions */
 unsigned int EF_ARM_APCS_26 ; 
 unsigned int EF_ARM_EABI_MASK ; 
 unsigned int EF_ARM_EABI_UNKNOWN ; 
 unsigned int EF_ARM_SOFT_FLOAT ; 
 unsigned int EF_ARM_VFP_FLOAT ; 
 scalar_t__ EM_ARM ; 
 int HWCAP_26BIT ; 
 int HWCAP_THUMB ; 
 int HWCAP_VFP ; 
 int elf_hwcap ; 

int elf_check_arch(const struct elf32_hdr *x)
{
	unsigned int eflags;

	/* Make sure it's an ARM executable */
	if (x->e_machine != EM_ARM)
		return 0;

	/* Make sure the entry address is reasonable */
	if (x->e_entry & 1) {
		if (!(elf_hwcap & HWCAP_THUMB))
			return 0;
	} else if (x->e_entry & 3)
		return 0;

	eflags = x->e_flags;
	if ((eflags & EF_ARM_EABI_MASK) == EF_ARM_EABI_UNKNOWN) {
		unsigned int flt_fmt;

		/* APCS26 is only allowed if the CPU supports it */
		if ((eflags & EF_ARM_APCS_26) && !(elf_hwcap & HWCAP_26BIT))
			return 0;

		flt_fmt = eflags & (EF_ARM_VFP_FLOAT | EF_ARM_SOFT_FLOAT);

		/* VFP requires the supporting code */
		if (flt_fmt == EF_ARM_VFP_FLOAT && !(elf_hwcap & HWCAP_VFP))
			return 0;
	}
	return 1;
}