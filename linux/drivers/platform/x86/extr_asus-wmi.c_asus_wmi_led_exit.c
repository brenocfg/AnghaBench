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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct asus_wmi {scalar_t__ led_workqueue; TYPE_1__ lightbar_led; TYPE_1__ wlan_led; TYPE_1__ tpd_led; TYPE_1__ kbd_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 

__attribute__((used)) static void asus_wmi_led_exit(struct asus_wmi *asus)
{
	if (!IS_ERR_OR_NULL(asus->kbd_led.dev))
		led_classdev_unregister(&asus->kbd_led);
	if (!IS_ERR_OR_NULL(asus->tpd_led.dev))
		led_classdev_unregister(&asus->tpd_led);
	if (!IS_ERR_OR_NULL(asus->wlan_led.dev))
		led_classdev_unregister(&asus->wlan_led);
	if (!IS_ERR_OR_NULL(asus->lightbar_led.dev))
		led_classdev_unregister(&asus->lightbar_led);
	if (asus->led_workqueue)
		destroy_workqueue(asus->led_workqueue);
}