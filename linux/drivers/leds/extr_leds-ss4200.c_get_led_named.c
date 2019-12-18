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
struct nasgpio_led {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nasgpio_led*) ; 
 struct nasgpio_led* nasgpio_leds ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct nasgpio_led *get_led_named(char *name)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(nasgpio_leds); i++) {
		if (strcmp(nasgpio_leds[i].name, name))
			continue;
		return &nasgpio_leds[i];
	}
	return NULL;
}