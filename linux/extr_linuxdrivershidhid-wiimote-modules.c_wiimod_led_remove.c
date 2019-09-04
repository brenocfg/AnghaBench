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
struct wiimote_data {int /*<<< orphan*/ ** leds; } ;
struct wiimod_ops {size_t arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wiimod_led_remove(const struct wiimod_ops *ops,
			      struct wiimote_data *wdata)
{
	if (!wdata->leds[ops->arg])
		return;

	led_classdev_unregister(wdata->leds[ops->arg]);
	kfree(wdata->leds[ops->arg]);
	wdata->leds[ops->arg] = NULL;
}