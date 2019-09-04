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
struct tca6507_led {scalar_t__ bank; scalar_t__ blink; struct tca6507_chip* chip; } ;
struct tca6507_chip {struct bank* bank; } ;
struct bank {int /*<<< orphan*/  level_use; int /*<<< orphan*/  time_use; } ;

/* Variables and functions */

__attribute__((used)) static void led_release(struct tca6507_led *led)
{
	/* If led owns any resource, release it. */
	struct tca6507_chip *tca = led->chip;
	if (led->bank >= 0) {
		struct bank *b = tca->bank + led->bank;
		if (led->blink)
			b->time_use--;
		b->level_use--;
	}
	led->blink = 0;
	led->bank = -1;
}