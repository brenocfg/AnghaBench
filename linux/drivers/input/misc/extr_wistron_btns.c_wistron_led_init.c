#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct device {int dummy; } ;
struct TYPE_4__ {void* brightness; } ;

/* Variables and functions */
 int FE_MAIL_LED ; 
 int FE_WIFI_LED ; 
 void* LED_FULL ; 
 void* LED_OFF ; 
 int /*<<< orphan*/  MAIL_LED ; 
 int /*<<< orphan*/  WIFI ; 
 int bios_get_default_setting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bios_set_state (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ led_classdev_register (struct device*,TYPE_1__*) ; 
 int leds_present ; 
 TYPE_1__ wistron_mail_led ; 
 TYPE_1__ wistron_wifi_led ; 

__attribute__((used)) static void wistron_led_init(struct device *parent)
{
	if (leds_present & FE_WIFI_LED) {
		u16 wifi = bios_get_default_setting(WIFI);
		if (wifi & 1) {
			wistron_wifi_led.brightness = (wifi & 2) ? LED_FULL : LED_OFF;
			if (led_classdev_register(parent, &wistron_wifi_led))
				leds_present &= ~FE_WIFI_LED;
			else
				bios_set_state(WIFI, wistron_wifi_led.brightness);

		} else
			leds_present &= ~FE_WIFI_LED;
	}

	if (leds_present & FE_MAIL_LED) {
		/* bios_get_default_setting(MAIL) always retuns 0, so just turn the led off */
		wistron_mail_led.brightness = LED_OFF;
		if (led_classdev_register(parent, &wistron_mail_led))
			leds_present &= ~FE_MAIL_LED;
		else
			bios_set_state(MAIL_LED, wistron_mail_led.brightness);
	}
}