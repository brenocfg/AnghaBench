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
 int W100_GPIO_PORT_A ; 
 scalar_t__ mmGPIO_DATA ; 
 scalar_t__ mmGPIO_DATA2 ; 
 scalar_t__ remapped_regs ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

void w100fb_gpio_write(int port, unsigned long value)
{
	if (port==W100_GPIO_PORT_A)
		writel(value, remapped_regs + mmGPIO_DATA);
	else
		writel(value, remapped_regs + mmGPIO_DATA2);
}