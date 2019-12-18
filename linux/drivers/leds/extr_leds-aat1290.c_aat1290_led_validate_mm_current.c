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
struct aat1290_led_config_data {scalar_t__ max_mm_current; int max_brightness; } ;
struct aat1290_led {scalar_t__* mm_current_scale; } ;

/* Variables and functions */
 int AAT1290_MM_CURRENT_SCALE_SIZE ; 

__attribute__((used)) static void aat1290_led_validate_mm_current(struct aat1290_led *led,
					struct aat1290_led_config_data *cfg)
{
	int i, b = 0, e = AAT1290_MM_CURRENT_SCALE_SIZE;

	while (e - b > 1) {
		i = b + (e - b) / 2;
		if (cfg->max_mm_current < led->mm_current_scale[i])
			e = i;
		else
			b = i;
	}

	cfg->max_mm_current = led->mm_current_scale[b];
	cfg->max_brightness = b + 1;
}