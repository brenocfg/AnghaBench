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
struct page {int dummy; } ;
struct cpa_data {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 scalar_t__ __split_large_page (struct cpa_data*,int /*<<< orphan*/ *,unsigned long,struct page*) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpa_lock ; 
 int /*<<< orphan*/  debug_pagealloc_enabled () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int split_large_page(struct cpa_data *cpa, pte_t *kpte,
			    unsigned long address)
{
	struct page *base;

	if (!debug_pagealloc_enabled())
		spin_unlock(&cpa_lock);
	base = alloc_pages(GFP_KERNEL, 0);
	if (!debug_pagealloc_enabled())
		spin_lock(&cpa_lock);
	if (!base)
		return -ENOMEM;

	if (__split_large_page(cpa, kpte, address, base))
		__free_page(base);

	return 0;
}