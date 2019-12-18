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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB3100_RTC ; 
 int abx500_mask_and_set_register_interruptible (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ab3100_rtc_irq_enable(struct device *dev, unsigned int enabled)
{
	/*
	 * It's not possible to enable/disable the alarm IRQ for this RTC.
	 * It does not actually trigger any IRQ: instead its only function is
	 * to power up the system, if it wasn't on. This will manifest as
	 * a "power up cause" in the AB3100 power driver (battery charging etc)
	 * and need to be handled there instead.
	 */
	if (enabled)
		return abx500_mask_and_set_register_interruptible(dev, 0,
						    AB3100_RTC, (1 << 2),
						    1 << 2);
	else
		return abx500_mask_and_set_register_interruptible(dev, 0,
						    AB3100_RTC, (1 << 2),
						    0);
}