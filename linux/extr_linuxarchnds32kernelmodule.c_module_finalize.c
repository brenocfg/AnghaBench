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
struct module {int dummy; } ;
typedef  int /*<<< orphan*/  Elf_Shdr ;
typedef  int /*<<< orphan*/  Elf32_Ehdr ;

/* Variables and functions */

int
module_finalize(const Elf32_Ehdr * hdr, const Elf_Shdr * sechdrs,
		struct module *module)
{
	return 0;
}