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
struct devstate_stat_reg {int shift; int nbits; int start_id; int enable; int disable; scalar_t__ reg; } ;
struct devstate_info {struct devstate_stat_reg* stat; struct devstate_ctl_reg* ctl; } ;
struct devstate_ctl_reg {int shift; int nbits; int start_id; int enable; int disable; scalar_t__ reg; int /*<<< orphan*/  enable_only; } ;
typedef  enum dscr_devstate_t { ____Placeholder_dscr_devstate_t } dscr_devstate_t ;
struct TYPE_2__ {scalar_t__ base; int /*<<< orphan*/  lock; struct devstate_info* devstate_info; } ;

/* Variables and functions */
#define  DSCR_DEVSTATE_DISABLED 129 
#define  DSCR_DEVSTATE_ENABLED 128 
 int MAX_DEVSTATE_IDS ; 
 TYPE_1__ dscr ; 
 int /*<<< orphan*/  dscr_write (scalar_t__,int) ; 
 int soc_readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dscr_set_devstate(int id, enum dscr_devstate_t state)
{
	struct devstate_ctl_reg *ctl;
	struct devstate_stat_reg *stat;
	struct devstate_info *info;
	u32 ctl_val, val;
	int ctl_shift, ctl_mask;
	unsigned long flags;

	if (!dscr.base)
		return;

	if (id < 0 || id >= MAX_DEVSTATE_IDS)
		return;

	info = &dscr.devstate_info[id];
	ctl = info->ctl;
	stat = info->stat;

	if (ctl == NULL)
		return;

	ctl_shift = ctl->shift + ctl->nbits * (id - ctl->start_id);
	ctl_mask = ((1 << ctl->nbits) - 1) << ctl_shift;

	switch (state) {
	case DSCR_DEVSTATE_ENABLED:
		ctl_val = ctl->enable << ctl_shift;
		break;
	case DSCR_DEVSTATE_DISABLED:
		if (ctl->enable_only)
			return;
		ctl_val = ctl->disable << ctl_shift;
		break;
	default:
		return;
	}

	spin_lock_irqsave(&dscr.lock, flags);

	val = soc_readl(dscr.base + ctl->reg);
	val &= ~ctl_mask;
	val |= ctl_val;

	dscr_write(ctl->reg, val);

	spin_unlock_irqrestore(&dscr.lock, flags);

	if (!stat)
		return;

	ctl_shift = stat->shift + stat->nbits * (id - stat->start_id);

	if (state == DSCR_DEVSTATE_ENABLED)
		ctl_val = stat->enable;
	else
		ctl_val = stat->disable;

	do {
		val = soc_readl(dscr.base + stat->reg);
		val >>= ctl_shift;
		val &= ((1 << stat->nbits) - 1);
	} while (val != ctl_val);
}