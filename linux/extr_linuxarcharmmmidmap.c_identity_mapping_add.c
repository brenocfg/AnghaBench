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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 scalar_t__ CPU_ARCH_ARMv5TEJ ; 
 unsigned long PMD_BIT4 ; 
 unsigned long PMD_SECT_AF ; 
 unsigned long PMD_SECT_AP_WRITE ; 
 unsigned long PMD_TYPE_SECT ; 
 scalar_t__ cpu_architecture () ; 
 int /*<<< orphan*/  cpu_is_xscale_family () ; 
 int /*<<< orphan*/  idmap_add_pud (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pgd_index (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,unsigned long) ; 
 unsigned long virt_to_idmap (char const*) ; 

__attribute__((used)) static void identity_mapping_add(pgd_t *pgd, const char *text_start,
				 const char *text_end, unsigned long prot)
{
	unsigned long addr, end;
	unsigned long next;

	addr = virt_to_idmap(text_start);
	end = virt_to_idmap(text_end);
	pr_info("Setting up static identity map for 0x%lx - 0x%lx\n", addr, end);

	prot |= PMD_TYPE_SECT | PMD_SECT_AP_WRITE | PMD_SECT_AF;

	if (cpu_architecture() <= CPU_ARCH_ARMv5TEJ && !cpu_is_xscale_family())
		prot |= PMD_BIT4;

	pgd += pgd_index(addr);
	do {
		next = pgd_addr_end(addr, end);
		idmap_add_pud(pgd, addr, next, prot);
	} while (pgd++, addr = next, addr != end);
}