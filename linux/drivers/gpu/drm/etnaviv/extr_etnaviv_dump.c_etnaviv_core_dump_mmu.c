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
struct etnaviv_iommu_context {int dummy; } ;
struct core_dump_iterator {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETDUMP_BUF_MMU ; 
 int /*<<< orphan*/  etnaviv_core_dump_header (struct core_dump_iterator*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  etnaviv_iommu_dump (struct etnaviv_iommu_context*,scalar_t__) ; 

__attribute__((used)) static void etnaviv_core_dump_mmu(struct core_dump_iterator *iter,
	struct etnaviv_iommu_context *mmu, size_t mmu_size)
{
	etnaviv_iommu_dump(mmu, iter->data);

	etnaviv_core_dump_header(iter, ETDUMP_BUF_MMU, iter->data + mmu_size);
}