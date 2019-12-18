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
typedef  int /*<<< orphan*/  u32 ;
struct ssb_extif {int /*<<< orphan*/  gpio_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_EXTIF_GPIO_INTPOL ; 
 int /*<<< orphan*/  extif_write32_masked (struct ssb_extif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u32 ssb_extif_gpio_polarity(struct ssb_extif *extif, u32 mask, u32 value)
{
	unsigned long flags;
	u32 res = 0;

	spin_lock_irqsave(&extif->gpio_lock, flags);
	res = extif_write32_masked(extif, SSB_EXTIF_GPIO_INTPOL, mask, value);
	spin_unlock_irqrestore(&extif->gpio_lock, flags);

	return res;
}