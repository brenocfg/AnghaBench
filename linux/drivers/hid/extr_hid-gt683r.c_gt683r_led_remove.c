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
struct hid_device {int dummy; } ;
struct gt683r_led {int /*<<< orphan*/  work; int /*<<< orphan*/ * led_devs; } ;

/* Variables and functions */
 int GT683R_LED_COUNT ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct gt683r_led* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gt683r_led_remove(struct hid_device *hdev)
{
	int i;
	struct gt683r_led *led = hid_get_drvdata(hdev);

	for (i = 0; i < GT683R_LED_COUNT; i++)
		led_classdev_unregister(&led->led_devs[i]);
	flush_work(&led->work);
	hid_hw_stop(hdev);
}