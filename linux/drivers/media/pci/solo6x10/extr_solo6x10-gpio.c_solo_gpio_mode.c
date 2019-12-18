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
 int /*<<< orphan*/  SOLO_GPIO_CONFIG_0 ; 
 int /*<<< orphan*/  SOLO_GPIO_CONFIG_1 ; 
 unsigned int solo_reg_read (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void solo_gpio_mode(struct solo_dev *solo_dev,
			   unsigned int port_mask, unsigned int mode)
{
	int port;
	unsigned int ret;

	ret = solo_reg_read(solo_dev, SOLO_GPIO_CONFIG_0);

	/* To set gpio */
	for (port = 0; port < 16; port++) {
		if (!((1 << port) & port_mask))
			continue;

		ret &= (~(3 << (port << 1)));
		ret |= ((mode & 3) << (port << 1));
	}

	solo_reg_write(solo_dev, SOLO_GPIO_CONFIG_0, ret);

	/* To set extended gpio - sensor */
	ret = solo_reg_read(solo_dev, SOLO_GPIO_CONFIG_1);

	for (port = 0; port < 16; port++) {
		if (!((1UL << (port + 16)) & port_mask))
			continue;

		if (!mode)
			ret &= ~(1UL << port);
		else
			ret |= 1UL << port;
	}

	/* Enable GPIO[31:16] */
	ret |= 0xffff0000;

	solo_reg_write(solo_dev, SOLO_GPIO_CONFIG_1, ret);
}