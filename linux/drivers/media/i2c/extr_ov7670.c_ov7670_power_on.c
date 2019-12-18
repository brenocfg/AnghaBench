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
struct v4l2_subdev {int dummy; } ;
struct ov7670_info {int on; scalar_t__ clk; scalar_t__ resetb_gpio; scalar_t__ pwdn_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ov7670_power_on(struct v4l2_subdev *sd)
{
	struct ov7670_info *info = to_state(sd);

	if (info->on)
		return;

	clk_prepare_enable(info->clk);

	if (info->pwdn_gpio)
		gpiod_set_value(info->pwdn_gpio, 0);
	if (info->resetb_gpio) {
		gpiod_set_value(info->resetb_gpio, 1);
		usleep_range(500, 1000);
		gpiod_set_value(info->resetb_gpio, 0);
	}
	if (info->pwdn_gpio || info->resetb_gpio || info->clk)
		usleep_range(3000, 5000);

	info->on = true;
}