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
struct phy_led_trigger {int /*<<< orphan*/  trigger; } ;
struct phy_device {scalar_t__ speed; struct phy_led_trigger* last_triggered; TYPE_1__* led_link_trigger; int /*<<< orphan*/  attached_dev; int /*<<< orphan*/  link; } ;
struct TYPE_2__ {int /*<<< orphan*/  trigger; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_alert (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 void phy_led_trigger_no_link (struct phy_device*) ; 
 struct phy_led_trigger* phy_speed_to_led_trigger (struct phy_device*,scalar_t__) ; 

void phy_led_trigger_change_speed(struct phy_device *phy)
{
	struct phy_led_trigger *plt;

	if (!phy->link)
		return phy_led_trigger_no_link(phy);

	if (phy->speed == 0)
		return;

	plt = phy_speed_to_led_trigger(phy, phy->speed);
	if (!plt) {
		netdev_alert(phy->attached_dev,
			     "No phy led trigger registered for speed(%d)\n",
			     phy->speed);
		return phy_led_trigger_no_link(phy);
	}

	if (plt != phy->last_triggered) {
		if (!phy->last_triggered)
			led_trigger_event(&phy->led_link_trigger->trigger,
					  LED_FULL);
		else
			led_trigger_event(&phy->last_triggered->trigger, LED_OFF);

		led_trigger_event(&plt->trigger, LED_FULL);
		phy->last_triggered = plt;
	}
}