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

/* Variables and functions */
 unsigned int LDC_MAP_DIRECT ; 
 unsigned int LDC_MAP_IO ; 
 unsigned int LDC_MAP_R ; 
 unsigned int LDC_MAP_SHADOW ; 
 unsigned int LDC_MAP_W ; 
 unsigned int LDC_MAP_X ; 
 int /*<<< orphan*/  LDC_MTE_COPY_R ; 
 int /*<<< orphan*/  LDC_MTE_COPY_W ; 
 int /*<<< orphan*/  LDC_MTE_EXEC ; 
 int /*<<< orphan*/  LDC_MTE_IOMMU_R ; 
 int /*<<< orphan*/  LDC_MTE_IOMMU_W ; 
 int /*<<< orphan*/  LDC_MTE_READ ; 
 int /*<<< orphan*/  LDC_MTE_WRITE ; 
 int /*<<< orphan*/  pagesize_code () ; 

__attribute__((used)) static u64 perm_to_mte(unsigned int map_perm)
{
	u64 mte_base;

	mte_base = pagesize_code();

	if (map_perm & LDC_MAP_SHADOW) {
		if (map_perm & LDC_MAP_R)
			mte_base |= LDC_MTE_COPY_R;
		if (map_perm & LDC_MAP_W)
			mte_base |= LDC_MTE_COPY_W;
	}
	if (map_perm & LDC_MAP_DIRECT) {
		if (map_perm & LDC_MAP_R)
			mte_base |= LDC_MTE_READ;
		if (map_perm & LDC_MAP_W)
			mte_base |= LDC_MTE_WRITE;
		if (map_perm & LDC_MAP_X)
			mte_base |= LDC_MTE_EXEC;
	}
	if (map_perm & LDC_MAP_IO) {
		if (map_perm & LDC_MAP_R)
			mte_base |= LDC_MTE_IOMMU_R;
		if (map_perm & LDC_MAP_W)
			mte_base |= LDC_MTE_IOMMU_W;
	}

	return mte_base;
}