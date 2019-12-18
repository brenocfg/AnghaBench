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
struct ipw2100_priv {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int IPW_BIT_GPIO_GPIO1_ENABLE ; 
 int IPW_BIT_GPIO_GPIO3_MASK ; 
 int IPW_BIT_GPIO_LED_OFF ; 
 int /*<<< orphan*/  IPW_REG_GPIO ; 
 int /*<<< orphan*/  write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ipw2100_hw_set_gpio(struct ipw2100_priv *priv)
{
	u32 reg = 0;
	/*
	 * Set GPIO 3 writable by FW; GPIO 1 writable
	 * by driver and enable clock
	 */
	reg = (IPW_BIT_GPIO_GPIO3_MASK | IPW_BIT_GPIO_GPIO1_ENABLE |
	       IPW_BIT_GPIO_LED_OFF);
	write_register(priv->net_dev, IPW_REG_GPIO, reg);
}