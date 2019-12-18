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
struct ssb_bus {int /*<<< orphan*/  gpio_lock; int /*<<< orphan*/  extif; int /*<<< orphan*/  chipco; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ ssb_chipco_available (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_chipco_gpio_polarity (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ssb_extif_available (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_extif_gpio_polarity (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 ssb_gpio_polarity(struct ssb_bus *bus, u32 mask, u32 value)
{
	unsigned long flags;
	u32 res = 0;

	spin_lock_irqsave(&bus->gpio_lock, flags);
	if (ssb_chipco_available(&bus->chipco))
		res = ssb_chipco_gpio_polarity(&bus->chipco, mask, value);
	else if (ssb_extif_available(&bus->extif))
		res = ssb_extif_gpio_polarity(&bus->extif, mask, value);
	else
		WARN_ON(1);
	spin_unlock_irqrestore(&bus->gpio_lock, flags);

	return res;
}