#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ssb_chipcommon {int /*<<< orphan*/  gpio_lock; TYPE_2__* dev; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_CHIPCO_GPIOPULLDOWN ; 
 int chipco_write32_masked (struct ssb_chipcommon*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u32 ssb_chipco_gpio_pulldown(struct ssb_chipcommon *cc, u32 mask, u32 value)
{
	unsigned long flags;
	u32 res = 0;

	if (cc->dev->id.revision < 20)
		return 0xffffffff;

	spin_lock_irqsave(&cc->gpio_lock, flags);
	res = chipco_write32_masked(cc, SSB_CHIPCO_GPIOPULLDOWN, mask, value);
	spin_unlock_irqrestore(&cc->gpio_lock, flags);

	return res;
}