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
struct remap_pfn {size_t i; int /*<<< orphan*/  mm; int /*<<< orphan*/  prot; struct page** pages; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkspecial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remap_pfn_fn(pte_t *ptep, unsigned long addr, void *data)
{
	struct remap_pfn *r = data;
	struct page *page = r->pages[r->i];
	pte_t pte = pte_mkspecial(pfn_pte(page_to_pfn(page), r->prot));

	set_pte_at(r->mm, addr, ptep, pte);
	r->i++;

	return 0;
}