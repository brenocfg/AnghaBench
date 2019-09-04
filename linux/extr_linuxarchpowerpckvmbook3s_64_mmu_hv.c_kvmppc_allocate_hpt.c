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
typedef  unsigned long u32 ;
struct revmap_entry {int dummy; } ;
struct page {int dummy; } ;
struct kvm_hpt_info {unsigned long order; unsigned long virt; int cma; struct revmap_entry* rev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PPC_MAX_HPT_ORDER ; 
 unsigned long PPC_MIN_HPT_ORDER ; 
 int __GFP_NOWARN ; 
 int __GFP_RETRY_MAYFAIL ; 
 int __GFP_ZERO ; 
 unsigned long __get_free_pages (int,unsigned long) ; 
 int /*<<< orphan*/  array_size (unsigned long,int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 struct page* kvm_alloc_hpt_cma (unsigned long) ; 
 int /*<<< orphan*/  kvm_free_hpt_cma (struct page*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 scalar_t__ pfn_to_kaddr (int /*<<< orphan*/ ) ; 
 struct revmap_entry* vmalloc (int /*<<< orphan*/ ) ; 

int kvmppc_allocate_hpt(struct kvm_hpt_info *info, u32 order)
{
	unsigned long hpt = 0;
	int cma = 0;
	struct page *page = NULL;
	struct revmap_entry *rev;
	unsigned long npte;

	if ((order < PPC_MIN_HPT_ORDER) || (order > PPC_MAX_HPT_ORDER))
		return -EINVAL;

	page = kvm_alloc_hpt_cma(1ul << (order - PAGE_SHIFT));
	if (page) {
		hpt = (unsigned long)pfn_to_kaddr(page_to_pfn(page));
		memset((void *)hpt, 0, (1ul << order));
		cma = 1;
	}

	if (!hpt)
		hpt = __get_free_pages(GFP_KERNEL|__GFP_ZERO|__GFP_RETRY_MAYFAIL
				       |__GFP_NOWARN, order - PAGE_SHIFT);

	if (!hpt)
		return -ENOMEM;

	/* HPTEs are 2**4 bytes long */
	npte = 1ul << (order - 4);

	/* Allocate reverse map array */
	rev = vmalloc(array_size(npte, sizeof(struct revmap_entry)));
	if (!rev) {
		if (cma)
			kvm_free_hpt_cma(page, 1 << (order - PAGE_SHIFT));
		else
			free_pages(hpt, order - PAGE_SHIFT);
		return -ENOMEM;
	}

	info->order = order;
	info->virt = hpt;
	info->cma = cma;
	info->rev = rev;

	return 0;
}