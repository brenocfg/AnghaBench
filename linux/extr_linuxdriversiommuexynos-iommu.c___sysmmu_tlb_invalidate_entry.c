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
typedef  int sysmmu_iova_t ;
struct sysmmu_drvdata {scalar_t__ sfrbase; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int MMU_MAJ_VER (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_MMU_FLUSH_ENTRY ; 
 scalar_t__ REG_V5_MMU_FLUSH_END ; 
 scalar_t__ REG_V5_MMU_FLUSH_ENTRY ; 
 scalar_t__ REG_V5_MMU_FLUSH_RANGE ; 
 scalar_t__ REG_V5_MMU_FLUSH_START ; 
 int SPAGE_MASK ; 
 int SPAGE_SIZE ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void __sysmmu_tlb_invalidate_entry(struct sysmmu_drvdata *data,
				sysmmu_iova_t iova, unsigned int num_inv)
{
	unsigned int i;

	if (MMU_MAJ_VER(data->version) < 5) {
		for (i = 0; i < num_inv; i++) {
			writel((iova & SPAGE_MASK) | 1,
				     data->sfrbase + REG_MMU_FLUSH_ENTRY);
			iova += SPAGE_SIZE;
		}
	} else {
		if (num_inv == 1) {
			writel((iova & SPAGE_MASK) | 1,
				     data->sfrbase + REG_V5_MMU_FLUSH_ENTRY);
		} else {
			writel((iova & SPAGE_MASK),
				     data->sfrbase + REG_V5_MMU_FLUSH_START);
			writel((iova & SPAGE_MASK) + (num_inv - 1) * SPAGE_SIZE,
				     data->sfrbase + REG_V5_MMU_FLUSH_END);
			writel(1, data->sfrbase + REG_V5_MMU_FLUSH_RANGE);
		}
	}
}