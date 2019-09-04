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
struct elf_shdr {int dummy; } ;
struct elf_info {int /*<<< orphan*/ * sechdrs; TYPE_1__* ehdr; } ;
struct TYPE_2__ {int e_shnum; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int elf_read_shdr (char const*,size_t,struct elf_info*,size_t) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elf_read_shdrs(const char *buf, size_t len,
			  struct elf_info *elf_info)
{
	size_t shdr_size, i;

	/*
	 * e_shnum is at most 65536 so calculating
	 * the size of the section header cannot overflow.
	 */
	shdr_size = sizeof(struct elf_shdr) * elf_info->ehdr->e_shnum;

	elf_info->sechdrs = kzalloc(shdr_size, GFP_KERNEL);
	if (!elf_info->sechdrs)
		return -ENOMEM;

	for (i = 0; i < elf_info->ehdr->e_shnum; i++) {
		int ret;

		ret = elf_read_shdr(buf, len, elf_info, i);
		if (ret) {
			kfree(elf_info->sechdrs);
			elf_info->sechdrs = NULL;
			return ret;
		}
	}

	return 0;
}