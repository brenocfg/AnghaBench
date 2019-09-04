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
struct TYPE_2__ {int /*<<< orphan*/  has_key_backlight; } ;

/* Variables and functions */
 int /*<<< orphan*/  applesmc_backlight ; 
 int /*<<< orphan*/  applesmc_led_wq ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 TYPE_1__ smcreg ; 

__attribute__((used)) static void applesmc_release_key_backlight(void)
{
	if (!smcreg.has_key_backlight)
		return;
	led_classdev_unregister(&applesmc_backlight);
	destroy_workqueue(applesmc_led_wq);
}