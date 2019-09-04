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
typedef  int u64 ;
struct ldc_mtable_entry {scalar_t__ mte; scalar_t__ cookie; } ;
struct ldc_iommu {struct ldc_mtable_entry* page_table; } ;

/* Variables and functions */
 int COOKIE_PGSZ_CODE_SHIFT ; 
 int /*<<< orphan*/  sun4v_ldc_revoke (unsigned long,int,scalar_t__) ; 

__attribute__((used)) static void ldc_demap(struct ldc_iommu *iommu, unsigned long id, u64 cookie,
		      unsigned long entry, unsigned long npages)
{
	struct ldc_mtable_entry *base;
	unsigned long i, shift;

	shift = (cookie >> COOKIE_PGSZ_CODE_SHIFT) * 3;
	base = iommu->page_table + entry;
	for (i = 0; i < npages; i++) {
		if (base->cookie)
			sun4v_ldc_revoke(id, cookie + (i << shift),
					 base->cookie);
		base->mte = 0;
	}
}