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
 unsigned int REG_PIN_03_SEL ; 
 unsigned int REG_PIN_47_SEL ; 

__attribute__((used)) static unsigned int meson_gpio_irq_channel_to_reg(unsigned int channel)
{
	return (channel < 4) ? REG_PIN_03_SEL : REG_PIN_47_SEL;
}