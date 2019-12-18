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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct phy_led_trigger {unsigned int speed; TYPE_1__ trigger; int /*<<< orphan*/  name; } ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int led_trigger_register (TYPE_1__*) ; 
 int /*<<< orphan*/  phy_led_trigger_format_name (struct phy_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_speed_to_str (unsigned int) ; 

__attribute__((used)) static int phy_led_trigger_register(struct phy_device *phy,
				    struct phy_led_trigger *plt,
				    unsigned int speed)
{
	plt->speed = speed;
	phy_led_trigger_format_name(phy, plt->name, sizeof(plt->name),
				    phy_speed_to_str(speed));
	plt->trigger.name = plt->name;

	return led_trigger_register(&plt->trigger);
}