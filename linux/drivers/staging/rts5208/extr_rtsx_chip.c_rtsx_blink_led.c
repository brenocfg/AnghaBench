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
struct rtsx_chip {scalar_t__ led_toggle_counter; scalar_t__ blink_led; scalar_t__ card_exist; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_GPIO ; 
 scalar_t__ LED_TOGGLE_INTERVAL ; 
 int /*<<< orphan*/  toggle_gpio (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rtsx_blink_led(struct rtsx_chip *chip)
{
	if (chip->card_exist && chip->blink_led) {
		if (chip->led_toggle_counter < LED_TOGGLE_INTERVAL) {
			chip->led_toggle_counter++;
		} else {
			chip->led_toggle_counter = 0;
			toggle_gpio(chip, LED_GPIO);
		}
	}
}