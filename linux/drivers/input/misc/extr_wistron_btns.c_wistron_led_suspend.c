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
 int FE_MAIL_LED ; 
 int FE_WIFI_LED ; 
 int /*<<< orphan*/  led_classdev_suspend (int /*<<< orphan*/ *) ; 
 int leds_present ; 
 int /*<<< orphan*/  wistron_mail_led ; 
 int /*<<< orphan*/  wistron_wifi_led ; 

__attribute__((used)) static inline void wistron_led_suspend(void)
{
	if (leds_present & FE_MAIL_LED)
		led_classdev_suspend(&wistron_mail_led);

	if (leds_present & FE_WIFI_LED)
		led_classdev_suspend(&wistron_wifi_led);
}