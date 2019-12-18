#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct em28xx_led {scalar_t__ role; } ;
struct TYPE_2__ {struct em28xx_led const* leds; } ;
struct em28xx {TYPE_1__ board; } ;
typedef  enum em28xx_led_role { ____Placeholder_em28xx_led_role } em28xx_led_role ;

/* Variables and functions */
 scalar_t__ EM28XX_NUM_LED_ROLES ; 

const struct em28xx_led *em28xx_find_led(struct em28xx *dev,
					 enum em28xx_led_role role)
{
	if (dev->board.leds) {
		u8 k = 0;

		while (dev->board.leds[k].role >= 0 &&
		       dev->board.leds[k].role < EM28XX_NUM_LED_ROLES) {
			if (dev->board.leds[k].role == role)
				return &dev->board.leds[k];
			k++;
		}
	}
	return NULL;
}