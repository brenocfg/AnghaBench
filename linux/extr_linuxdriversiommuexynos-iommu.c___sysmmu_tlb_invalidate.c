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
struct sysmmu_drvdata {scalar_t__ sfrbase; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int MMU_MAJ_VER (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_MMU_FLUSH ; 
 scalar_t__ REG_V5_MMU_FLUSH_ALL ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void __sysmmu_tlb_invalidate(struct sysmmu_drvdata *data)
{
	if (MMU_MAJ_VER(data->version) < 5)
		writel(0x1, data->sfrbase + REG_MMU_FLUSH);
	else
		writel(0x1, data->sfrbase + REG_V5_MMU_FLUSH_ALL);
}