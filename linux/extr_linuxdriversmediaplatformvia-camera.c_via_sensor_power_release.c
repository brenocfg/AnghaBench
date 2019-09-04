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
struct via_camera {int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  power_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via_sensor_power_down (struct via_camera*) ; 

__attribute__((used)) static void via_sensor_power_release(struct via_camera *cam)
{
	via_sensor_power_down(cam);
	gpio_free(cam->power_gpio);
	gpio_free(cam->reset_gpio);
}