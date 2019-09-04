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
struct iommu_table {scalar_t__* it_userspace; int it_indirect_levels; int it_level_size; int /*<<< orphan*/  it_nid; scalar_t__ it_base; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 unsigned long TCE_PCI_READ ; 
 unsigned long TCE_PCI_WRITE ; 
 unsigned long __pa (scalar_t__*) ; 
 scalar_t__* __va (unsigned long) ; 
 unsigned long be64_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be64 (unsigned long) ; 
 int ilog2 (int) ; 
 scalar_t__* pnv_alloc_tce_level (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __be64 *pnv_tce(struct iommu_table *tbl, bool user, long idx, bool alloc)
{
	__be64 *tmp = user ? tbl->it_userspace : (__be64 *) tbl->it_base;
	int  level = tbl->it_indirect_levels;
	const long shift = ilog2(tbl->it_level_size);
	unsigned long mask = (tbl->it_level_size - 1) << (level * shift);

	while (level) {
		int n = (idx & mask) >> (level * shift);
		unsigned long tce;

		if (tmp[n] == 0) {
			__be64 *tmp2;

			if (!alloc)
				return NULL;

			tmp2 = pnv_alloc_tce_level(tbl->it_nid,
					ilog2(tbl->it_level_size) + 3);
			if (!tmp2)
				return NULL;

			tmp[n] = cpu_to_be64(__pa(tmp2) |
					TCE_PCI_READ | TCE_PCI_WRITE);
		}
		tce = be64_to_cpu(tmp[n]);

		tmp = __va(tce & ~(TCE_PCI_READ | TCE_PCI_WRITE));
		idx &= ~mask;
		mask >>= shift;
		--level;
	}

	return tmp + idx;
}