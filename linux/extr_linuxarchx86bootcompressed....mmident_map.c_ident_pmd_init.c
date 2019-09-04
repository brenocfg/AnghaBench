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
struct x86_mapping_info {unsigned long offset; unsigned long page_flag; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long PMD_MASK ; 
 scalar_t__ PMD_SIZE ; 
 int /*<<< orphan*/  __pmd (unsigned long) ; 
 int pmd_index (unsigned long) ; 
 scalar_t__ pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ident_pmd_init(struct x86_mapping_info *info, pmd_t *pmd_page,
			   unsigned long addr, unsigned long end)
{
	addr &= PMD_MASK;
	for (; addr < end; addr += PMD_SIZE) {
		pmd_t *pmd = pmd_page + pmd_index(addr);

		if (pmd_present(*pmd))
			continue;

		set_pmd(pmd, __pmd((addr - info->offset) | info->page_flag));
	}
}