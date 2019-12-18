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
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int TPACPI_LED_MAX ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 TYPE_1__* led_tables ; 
 int /*<<< orphan*/ * mute_led_cdev ; 
 int /*<<< orphan*/  tpacpi_led_set (int,int) ; 

__attribute__((used)) static void mute_led_exit(void)
{
	int i;

	for (i = 0; i < TPACPI_LED_MAX; i++) {
		if (led_tables[i].state >= 0) {
			led_classdev_unregister(&mute_led_cdev[i]);
			tpacpi_led_set(i, false);
		}
	}
}