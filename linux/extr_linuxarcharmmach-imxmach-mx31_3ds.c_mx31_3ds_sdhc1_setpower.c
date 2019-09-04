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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MX31_3DS_GPIO_SDHC1_BE ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mx31_3ds_sdhc1_setpower(struct device *dev, unsigned int vdd)
{
	/*
	 * While the voltage stuff is done by the driver, activate the
	 * Buffer Enable Pin only if there is a card in slot to fix the card
	 * voltage issue caused by bi-directional chip TXB0108 on 3Stack.
	 * Done here because at this stage we have for sure a debounced value
	 * of the presence of the card, showed by the value of vdd.
	 * 7 == ilog2(MMC_VDD_165_195)
	 */
	if (vdd > 7)
		gpio_set_value(MX31_3DS_GPIO_SDHC1_BE, 1);
	else
		gpio_set_value(MX31_3DS_GPIO_SDHC1_BE, 0);
}