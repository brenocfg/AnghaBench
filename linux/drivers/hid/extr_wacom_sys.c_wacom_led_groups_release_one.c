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
struct wacom_group_leds {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devres_release_group (int /*<<< orphan*/ ,struct wacom_group_leds*) ; 

__attribute__((used)) static void wacom_led_groups_release_one(void *data)
{
	struct wacom_group_leds *group = data;

	devres_release_group(group->dev, group);
}