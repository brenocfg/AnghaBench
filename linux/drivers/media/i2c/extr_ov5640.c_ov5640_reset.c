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
struct ov5640_dev {int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ov5640_power (struct ov5640_dev*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ov5640_reset(struct ov5640_dev *sensor)
{
	if (!sensor->reset_gpio)
		return;

	gpiod_set_value_cansleep(sensor->reset_gpio, 0);

	/* camera power cycle */
	ov5640_power(sensor, false);
	usleep_range(5000, 10000);
	ov5640_power(sensor, true);
	usleep_range(5000, 10000);

	gpiod_set_value_cansleep(sensor->reset_gpio, 1);
	usleep_range(1000, 2000);

	gpiod_set_value_cansleep(sensor->reset_gpio, 0);
	usleep_range(20000, 25000);
}