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
struct mt9v111_dev {int /*<<< orphan*/  oe; int /*<<< orphan*/  standby; int /*<<< orphan*/  sysclk; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct mt9v111_dev* sd_to_mt9v111 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int __mt9v111_power_on(struct v4l2_subdev *sd)
{
	struct mt9v111_dev *mt9v111 = sd_to_mt9v111(sd);
	int ret;

	ret = clk_prepare_enable(mt9v111->clk);
	if (ret)
		return ret;

	clk_set_rate(mt9v111->clk, mt9v111->sysclk);

	gpiod_set_value(mt9v111->standby, 0);
	usleep_range(500, 1000);

	gpiod_set_value(mt9v111->oe, 1);
	usleep_range(500, 1000);

	return 0;
}