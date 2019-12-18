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
struct b53_device {int reset_gpio; int current_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void b53_switch_reset_gpio(struct b53_device *dev)
{
	int gpio = dev->reset_gpio;

	if (gpio < 0)
		return;

	/* Reset sequence: RESET low(50ms)->high(20ms)
	 */
	gpio_set_value(gpio, 0);
	mdelay(50);

	gpio_set_value(gpio, 1);
	mdelay(20);

	dev->current_page = 0xff;
}