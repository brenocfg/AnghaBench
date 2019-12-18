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

__attribute__((used)) static unsigned int tegra_gpio_compose(unsigned int bank, unsigned int port,
				       unsigned int bit)
{
	return (bank << 5) | ((port & 0x3) << 3) | (bit & 0x7);
}