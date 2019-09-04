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
struct file {int dummy; } ;
struct elfhdr {int dummy; } ;
struct elf_phdr {int dummy; } ;
struct arch_elf_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int arch_elf_pt_proc(struct elfhdr *ehdr,
				   struct elf_phdr *phdr,
				   struct file *elf, bool is_interp,
				   struct arch_elf_state *state)
{
	/* Dummy implementation, always proceed */
	return 0;
}