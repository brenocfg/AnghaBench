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
typedef  int /*<<< orphan*/  u64 ;
struct cpa_data {unsigned long* vaddr; unsigned int numpages; void* mask_set; void* mask_clr; int /*<<< orphan*/  flags; int /*<<< orphan*/ * pgd; int /*<<< orphan*/  pfn; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long _PAGE_ENC ; 
 unsigned long _PAGE_NX ; 
 unsigned long _PAGE_PRESENT ; 
 unsigned long _PAGE_RW ; 
 int __change_page_attr_set_clr (struct cpa_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __flush_tlb_all () ; 
 void* __pgprot (unsigned long) ; 
 unsigned long __supported_pte_mask ; 
 void* pgprot_encrypted (void*) ; 

int kernel_map_pages_in_pgd(pgd_t *pgd, u64 pfn, unsigned long address,
			    unsigned numpages, unsigned long page_flags)
{
	int retval = -EINVAL;

	struct cpa_data cpa = {
		.vaddr = &address,
		.pfn = pfn,
		.pgd = pgd,
		.numpages = numpages,
		.mask_set = __pgprot(0),
		.mask_clr = __pgprot(0),
		.flags = 0,
	};

	if (!(__supported_pte_mask & _PAGE_NX))
		goto out;

	if (!(page_flags & _PAGE_NX))
		cpa.mask_clr = __pgprot(_PAGE_NX);

	if (!(page_flags & _PAGE_RW))
		cpa.mask_clr = __pgprot(_PAGE_RW);

	if (!(page_flags & _PAGE_ENC))
		cpa.mask_clr = pgprot_encrypted(cpa.mask_clr);

	cpa.mask_set = __pgprot(_PAGE_PRESENT | page_flags);

	retval = __change_page_attr_set_clr(&cpa, 0);
	__flush_tlb_all();

out:
	return retval;
}