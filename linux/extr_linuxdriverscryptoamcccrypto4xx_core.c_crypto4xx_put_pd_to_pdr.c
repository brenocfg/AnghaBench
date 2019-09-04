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
typedef  size_t u32 ;
struct pd_uinfo {int /*<<< orphan*/  state; } ;
struct crypto4xx_device {scalar_t__ pdr_tail; TYPE_1__* core_dev; struct pd_uinfo* pdr_uinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PD_ENTRY_FREE ; 
 scalar_t__ PPC4XX_LAST_PD ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u32 crypto4xx_put_pd_to_pdr(struct crypto4xx_device *dev, u32 idx)
{
	struct pd_uinfo *pd_uinfo = &dev->pdr_uinfo[idx];
	u32 tail;
	unsigned long flags;

	spin_lock_irqsave(&dev->core_dev->lock, flags);
	pd_uinfo->state = PD_ENTRY_FREE;

	if (dev->pdr_tail != PPC4XX_LAST_PD)
		dev->pdr_tail++;
	else
		dev->pdr_tail = 0;
	tail = dev->pdr_tail;
	spin_unlock_irqrestore(&dev->core_dev->lock, flags);

	return tail;
}