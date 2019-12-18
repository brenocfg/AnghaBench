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
struct p54_common {int /*<<< orphan*/  led_work; TYPE_1__* leds; } ;
struct TYPE_2__ {int registered; int /*<<< orphan*/  led_dev; scalar_t__ toggled; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

void p54_unregister_leds(struct p54_common *priv)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(priv->leds); i++) {
		if (priv->leds[i].registered) {
			priv->leds[i].registered = false;
			priv->leds[i].toggled = 0;
			led_classdev_unregister(&priv->leds[i].led_dev);
		}
	}

	cancel_delayed_work_sync(&priv->led_work);
}