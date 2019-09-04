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
typedef  int /*<<< orphan*/  sysmmu_iova_t ;
struct sysmmu_drvdata {scalar_t__ version; int /*<<< orphan*/  lock; int /*<<< orphan*/  clk_master; scalar_t__ active; } ;

/* Variables and functions */
 scalar_t__ MAKE_MMU_VER (int,int) ; 
 int /*<<< orphan*/  __sysmmu_tlb_invalidate (struct sysmmu_drvdata*) ; 
 int /*<<< orphan*/  __sysmmu_tlb_invalidate_entry (struct sysmmu_drvdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ sysmmu_block (struct sysmmu_drvdata*) ; 
 int /*<<< orphan*/  sysmmu_unblock (struct sysmmu_drvdata*) ; 

__attribute__((used)) static void sysmmu_tlb_invalidate_flpdcache(struct sysmmu_drvdata *data,
					    sysmmu_iova_t iova)
{
	unsigned long flags;

	spin_lock_irqsave(&data->lock, flags);
	if (data->active && data->version >= MAKE_MMU_VER(3, 3)) {
		clk_enable(data->clk_master);
		if (sysmmu_block(data)) {
			if (data->version >= MAKE_MMU_VER(5, 0))
				__sysmmu_tlb_invalidate(data);
			else
				__sysmmu_tlb_invalidate_entry(data, iova, 1);
			sysmmu_unblock(data);
		}
		clk_disable(data->clk_master);
	}
	spin_unlock_irqrestore(&data->lock, flags);
}