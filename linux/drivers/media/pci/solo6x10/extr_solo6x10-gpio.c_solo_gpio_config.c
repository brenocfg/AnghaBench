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
struct solo_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  solo_gpio_clear (struct solo_dev*,int) ; 
 int /*<<< orphan*/  solo_gpio_mode (struct solo_dev*,int,int) ; 
 int /*<<< orphan*/  solo_gpio_set (struct solo_dev*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void solo_gpio_config(struct solo_dev *solo_dev)
{
	/* Video reset */
	solo_gpio_mode(solo_dev, 0x30, 1);
	solo_gpio_clear(solo_dev, 0x30);
	udelay(100);
	solo_gpio_set(solo_dev, 0x30);
	udelay(100);

	/* Warning: Don't touch the next line unless you're sure of what
	 * you're doing: first four gpio [0-3] are used for video. */
	solo_gpio_mode(solo_dev, 0x0f, 2);

	/* We use bit 8-15 of SOLO_GPIO_CONFIG_0 for relay purposes */
	solo_gpio_mode(solo_dev, 0xff00, 1);

	/* Initially set relay status to 0 */
	solo_gpio_clear(solo_dev, 0xff00);

	/* Set input pins direction */
	solo_gpio_mode(solo_dev, 0xffff0000, 0);
}