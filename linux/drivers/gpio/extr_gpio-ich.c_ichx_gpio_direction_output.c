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
struct gpio_chip {int dummy; } ;
struct TYPE_4__ {TYPE_1__* desc; } ;
struct TYPE_3__ {scalar_t__ have_blink; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_IO_SEL ; 
 int /*<<< orphan*/  GPIO_LVL ; 
 int /*<<< orphan*/  GPO_BLINK ; 
 TYPE_2__ ichx_priv ; 
 int ichx_write_bit (int /*<<< orphan*/ ,unsigned int,int,int) ; 

__attribute__((used)) static int ichx_gpio_direction_output(struct gpio_chip *gpio, unsigned nr,
					int val)
{
	/* Disable blink hardware which is available for GPIOs from 0 to 31. */
	if (nr < 32 && ichx_priv.desc->have_blink)
		ichx_write_bit(GPO_BLINK, nr, 0, 0);

	/* Set GPIO output value. */
	ichx_write_bit(GPIO_LVL, nr, val, 0);

	/*
	 * Try setting pin as an output and verify it worked since many pins
	 * are input-only.
	 */
	return ichx_write_bit(GPIO_IO_SEL, nr, 0, 1);
}