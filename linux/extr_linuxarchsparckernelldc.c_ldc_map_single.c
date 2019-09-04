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
struct ldc_trans_cookie {int dummy; } ;
struct ldc_mtable_entry {int dummy; } ;
struct ldc_iommu {int page_table; } ;
struct ldc_channel {struct ldc_iommu iommu; } ;
struct cookie_state {int page_table; int nc; struct ldc_mtable_entry* pte_idx; int /*<<< orphan*/  prev_cookie; int /*<<< orphan*/  mte_base; struct ldc_trans_cookie* cookies; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int LDC_MAP_ALL ; 
 unsigned long PAGE_MASK ; 
 unsigned long __pa (void*) ; 
 struct ldc_mtable_entry* alloc_npages (struct ldc_iommu*,unsigned long) ; 
 int /*<<< orphan*/  fill_cookies (struct cookie_state*,unsigned long,unsigned long,unsigned int) ; 
 unsigned long pages_in_region (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  perm_to_mte (unsigned int) ; 

int ldc_map_single(struct ldc_channel *lp,
		   void *buf, unsigned int len,
		   struct ldc_trans_cookie *cookies, int ncookies,
		   unsigned int map_perm)
{
	unsigned long npages, pa;
	struct ldc_mtable_entry *base;
	struct cookie_state state;
	struct ldc_iommu *iommu;

	if ((map_perm & ~LDC_MAP_ALL) || (ncookies < 1))
		return -EINVAL;

	pa = __pa(buf);
	if ((pa | len) & (8UL - 1))
		return -EFAULT;

	npages = pages_in_region(pa, len);

	iommu = &lp->iommu;

	base = alloc_npages(iommu, npages);

	if (!base)
		return -ENOMEM;

	state.page_table = iommu->page_table;
	state.cookies = cookies;
	state.mte_base = perm_to_mte(map_perm);
	state.prev_cookie = ~(u64)0;
	state.pte_idx = (base - iommu->page_table);
	state.nc = 0;
	fill_cookies(&state, (pa & PAGE_MASK), (pa & ~PAGE_MASK), len);
	BUG_ON(state.nc > ncookies);

	return state.nc;
}