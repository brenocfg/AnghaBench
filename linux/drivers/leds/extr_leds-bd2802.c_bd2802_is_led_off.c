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
struct bd2802_led {TYPE_1__* led; } ;
typedef  enum led_ids { ____Placeholder_led_ids } led_ids ;
struct TYPE_2__ {scalar_t__ b; scalar_t__ g; scalar_t__ r; } ;

/* Variables and functions */

__attribute__((used)) static inline int bd2802_is_led_off(struct bd2802_led *led, enum led_ids id)
{
	if (led->led[id].r || led->led[id].g || led->led[id].b)
		return 0;

	return 1;
}