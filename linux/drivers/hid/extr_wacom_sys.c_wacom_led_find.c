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
struct wacom_led {int dummy; } ;
struct wacom_group_leds {unsigned int count; struct wacom_led* leds; } ;
struct TYPE_2__ {unsigned int count; struct wacom_group_leds* groups; } ;
struct wacom {TYPE_1__ led; } ;

/* Variables and functions */

struct wacom_led *wacom_led_find(struct wacom *wacom, unsigned int group_id,
				 unsigned int id)
{
	struct wacom_group_leds *group;

	if (group_id >= wacom->led.count)
		return NULL;

	group = &wacom->led.groups[group_id];

	if (!group->leds)
		return NULL;

	id %= group->count;

	return &group->leds[id];
}