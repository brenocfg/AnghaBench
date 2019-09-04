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
struct bd2802_led {int dummy; } ;

/* Variables and functions */
 int LED_NUM ; 
 int /*<<< orphan*/  bd2802_is_led_off (struct bd2802_led*,int) ; 

__attribute__((used)) static inline int bd2802_is_all_off(struct bd2802_led *led)
{
	int i;

	for (i = 0; i < LED_NUM; i++)
		if (!bd2802_is_led_off(led, i))
			return 0;

	return 1;
}