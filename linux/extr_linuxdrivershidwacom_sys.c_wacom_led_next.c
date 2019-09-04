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
struct TYPE_2__ {int /*<<< orphan*/ * trigger; } ;
struct wacom_led {int group; int id; int /*<<< orphan*/  trigger; TYPE_1__ cdev; } ;
struct wacom {int dummy; } ;

/* Variables and functions */
 struct wacom_led* wacom_led_find (struct wacom*,int,int) ; 

struct wacom_led *wacom_led_next(struct wacom *wacom, struct wacom_led *cur)
{
	struct wacom_led *next_led;
	int group, next;

	if (!wacom || !cur)
		return NULL;

	group = cur->group;
	next = cur->id;

	do {
		next_led = wacom_led_find(wacom, group, ++next);
		if (!next_led || next_led == cur)
			return next_led;
	} while (next_led->cdev.trigger != &next_led->trigger);

	return next_led;
}