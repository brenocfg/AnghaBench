#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ppc64_stub_entry {int /*<<< orphan*/  funcdata; } ;
struct TYPE_5__ {size_t stubs_section; } ;
struct module {TYPE_1__ arch; } ;
struct TYPE_6__ {int sh_size; scalar_t__ sh_addr; } ;
typedef  TYPE_2__ Elf64_Shdr ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  create_stub (TYPE_2__ const*,struct ppc64_stub_entry*,unsigned long,struct module*) ; 
 scalar_t__ func_addr (unsigned long) ; 
 scalar_t__ stub_func_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long stub_for_addr(const Elf64_Shdr *sechdrs,
				   unsigned long addr,
				   struct module *me)
{
	struct ppc64_stub_entry *stubs;
	unsigned int i, num_stubs;

	num_stubs = sechdrs[me->arch.stubs_section].sh_size / sizeof(*stubs);

	/* Find this stub, or if that fails, the next avail. entry */
	stubs = (void *)sechdrs[me->arch.stubs_section].sh_addr;
	for (i = 0; stub_func_addr(stubs[i].funcdata); i++) {
		if (WARN_ON(i >= num_stubs))
			return 0;

		if (stub_func_addr(stubs[i].funcdata) == func_addr(addr))
			return (unsigned long)&stubs[i];
	}

	if (!create_stub(sechdrs, &stubs[i], addr, me))
		return 0;

	return (unsigned long)&stubs[i];
}