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
 int /*<<< orphan*/  GPIO_NR_PALMTC_PCMCIA_POWER1 ; 
 int /*<<< orphan*/  GPIO_NR_PALMTC_PCMCIA_POWER2 ; 
 int /*<<< orphan*/  GPIO_NR_PALMTC_PCMCIA_POWER3 ; 
 int /*<<< orphan*/  GPIO_NR_PALMTC_PCMCIA_PWRREADY ; 
 int /*<<< orphan*/  GPIO_NR_PALMTC_PCMCIA_RESET ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  palmtc_wifi_powerdown () ; 

__attribute__((used)) static int palmtc_wifi_powerup(void)
{
	int timeout = 50;

	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER3, 1);
	mdelay(50);

	/* Power up the card, 1.8V first, after a while 3.3V */
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER1, 1);
	mdelay(100);
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER2, 1);

	/* Wait till the card is ready */
	while (!gpio_get_value(GPIO_NR_PALMTC_PCMCIA_PWRREADY) &&
		timeout) {
		mdelay(1);
		timeout--;
	}

	/* Power down the WiFi in case of error */
	if (!timeout) {
		palmtc_wifi_powerdown();
		return 1;
	}

	/* Reset the card */
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_RESET, 1);
	mdelay(20);
	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_RESET, 0);
	mdelay(25);

	gpio_set_value(GPIO_NR_PALMTC_PCMCIA_POWER3, 0);

	return 0;
}