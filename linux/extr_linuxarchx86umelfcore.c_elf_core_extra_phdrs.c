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
struct elfhdr {int /*<<< orphan*/  e_phnum; } ;
typedef  int /*<<< orphan*/  Elf32_Half ;

/* Variables and functions */
 scalar_t__ vsyscall_ehdr ; 

Elf32_Half elf_core_extra_phdrs(void)
{
	return vsyscall_ehdr ? (((struct elfhdr *)vsyscall_ehdr)->e_phnum) : 0;
}