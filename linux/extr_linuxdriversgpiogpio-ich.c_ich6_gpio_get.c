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
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pm_base; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int ENXIO ; 
 int ICHX_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICHX_WRITE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ichx_gpio_get (struct gpio_chip*,unsigned int) ; 
 TYPE_1__ ichx_priv ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ich6_gpio_get(struct gpio_chip *chip, unsigned nr)
{
	unsigned long flags;
	u32 data;

	/*
	 * GPI 0 - 15 need to be read from the power management registers on
	 * a ICH6/3100 bridge.
	 */
	if (nr < 16) {
		if (!ichx_priv.pm_base)
			return -ENXIO;

		spin_lock_irqsave(&ichx_priv.lock, flags);

		/* GPI 0 - 15 are latched, write 1 to clear*/
		ICHX_WRITE(BIT(16 + nr), 0, ichx_priv.pm_base);
		data = ICHX_READ(0, ichx_priv.pm_base);

		spin_unlock_irqrestore(&ichx_priv.lock, flags);

		return !!((data >> 16) & BIT(nr));
	} else {
		return ichx_gpio_get(chip, nr);
	}
}