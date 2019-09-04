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
struct elfhdr {int dummy; } ;
struct elf_info {int dummy; } ;

/* Variables and functions */
 int ENOEXEC ; 
 int build_elf_exec_info (char const*,unsigned long,struct elfhdr*,struct elf_info*) ; 
 scalar_t__ elf_check_arch (struct elfhdr*) ; 
 int /*<<< orphan*/  elf_free_info (struct elf_info*) ; 

__attribute__((used)) static int elf64_probe(const char *buf, unsigned long len)
{
	struct elfhdr ehdr;
	struct elf_info elf_info;
	int ret;

	ret = build_elf_exec_info(buf, len, &ehdr, &elf_info);
	if (ret)
		return ret;

	elf_free_info(&elf_info);

	return elf_check_arch(&ehdr) ? 0 : -ENOEXEC;
}