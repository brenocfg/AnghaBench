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
typedef  int u32 ;
struct bcm2835_pinctrl {int dummy; } ;

/* Variables and functions */
 scalar_t__ GP_GPIO_PUP_PDN_CNTRL_REG0 ; 
 int PUD_2711_MASK ; 
 int PUD_2711_REG_OFFSET (unsigned int) ; 
 int PUD_2711_REG_SHIFT (unsigned int) ; 
 int bcm2835_gpio_rd (struct bcm2835_pinctrl*,scalar_t__) ; 
 int /*<<< orphan*/  bcm2835_gpio_wr (struct bcm2835_pinctrl*,scalar_t__,int) ; 

__attribute__((used)) static void bcm2711_pull_config_set(struct bcm2835_pinctrl *pc,
				    unsigned int pin, unsigned int arg)
{
	u32 shifter;
	u32 value;
	u32 off;

	off = PUD_2711_REG_OFFSET(pin);
	shifter = PUD_2711_REG_SHIFT(pin);

	value = bcm2835_gpio_rd(pc, GP_GPIO_PUP_PDN_CNTRL_REG0 + (off * 4));
	value &= ~(PUD_2711_MASK << shifter);
	value |= (arg << shifter);
	bcm2835_gpio_wr(pc, GP_GPIO_PUP_PDN_CNTRL_REG0 + (off * 4), value);
}