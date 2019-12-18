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
typedef  int /*<<< orphan*/  u8 ;
struct lp55xx_led {scalar_t__ chan_nr; int /*<<< orphan*/  chip; int /*<<< orphan*/  led_current; } ;

/* Variables and functions */
 scalar_t__ LP5521_REG_LED_CURRENT_BASE ; 
 int /*<<< orphan*/  lp55xx_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lp5521_set_led_current(struct lp55xx_led *led, u8 led_current)
{
	led->led_current = led_current;
	lp55xx_write(led->chip, LP5521_REG_LED_CURRENT_BASE + led->chan_nr,
		led_current);
}