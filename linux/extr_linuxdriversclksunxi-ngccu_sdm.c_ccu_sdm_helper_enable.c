#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ccu_sdm_internal {unsigned int table_size; int tuning_enable; int enable; scalar_t__ tuning_reg; TYPE_1__* table; } ;
struct ccu_common {int features; int /*<<< orphan*/  lock; scalar_t__ reg; scalar_t__ base; } ;
struct TYPE_2__ {unsigned long rate; int pattern; } ;

/* Variables and functions */
 int CCU_FEATURE_SIGMA_DELTA_MOD ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void ccu_sdm_helper_enable(struct ccu_common *common,
			   struct ccu_sdm_internal *sdm,
			   unsigned long rate)
{
	unsigned long flags;
	unsigned int i;
	u32 reg;

	if (!(common->features & CCU_FEATURE_SIGMA_DELTA_MOD))
		return;

	/* Set the pattern */
	for (i = 0; i < sdm->table_size; i++)
		if (sdm->table[i].rate == rate)
			writel(sdm->table[i].pattern,
			       common->base + sdm->tuning_reg);

	/* Make sure SDM is enabled */
	spin_lock_irqsave(common->lock, flags);
	reg = readl(common->base + sdm->tuning_reg);
	writel(reg | sdm->tuning_enable, common->base + sdm->tuning_reg);
	spin_unlock_irqrestore(common->lock, flags);

	spin_lock_irqsave(common->lock, flags);
	reg = readl(common->base + common->reg);
	writel(reg | sdm->enable, common->base + common->reg);
	spin_unlock_irqrestore(common->lock, flags);
}