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

/* Variables and functions */
 unsigned int* IXP4XX_OSRT2 ; 
 unsigned int IXP4XX_OST_ENABLE ; 
 unsigned int IXP4XX_OST_RELOAD_MASK ; 
 int /*<<< orphan*/  beep_lock ; 
 int /*<<< orphan*/  gpio_direction_input (unsigned int) ; 
 int /*<<< orphan*/  gpio_direction_output (unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ixp4xx_spkr_control(unsigned int pin, unsigned int count)
{
	unsigned long flags;

	spin_lock_irqsave(&beep_lock, flags);

	if (count) {
		gpio_direction_output(pin, 0);
		*IXP4XX_OSRT2 = (count & ~IXP4XX_OST_RELOAD_MASK) | IXP4XX_OST_ENABLE;
	} else {
		gpio_direction_output(pin, 1);
		gpio_direction_input(pin);
		*IXP4XX_OSRT2 = 0;
	}

	spin_unlock_irqrestore(&beep_lock, flags);
}