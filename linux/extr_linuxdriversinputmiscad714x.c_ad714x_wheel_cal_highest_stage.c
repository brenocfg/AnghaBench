#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ad714x_wheel_plat {int /*<<< orphan*/  end_stage; int /*<<< orphan*/  start_stage; } ;
struct ad714x_wheel_drv {int /*<<< orphan*/  highest_stage; int /*<<< orphan*/  pre_highest_stage; } ;
struct ad714x_chip {int /*<<< orphan*/  dev; TYPE_2__* sw; TYPE_1__* hw; } ;
struct TYPE_4__ {struct ad714x_wheel_drv* wheel; } ;
struct TYPE_3__ {struct ad714x_wheel_plat* wheel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad714x_cal_highest_stage (struct ad714x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad714x_wheel_cal_highest_stage(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_wheel_plat *hw = &ad714x->hw->wheel[idx];
	struct ad714x_wheel_drv *sw = &ad714x->sw->wheel[idx];

	sw->pre_highest_stage = sw->highest_stage;
	sw->highest_stage = ad714x_cal_highest_stage(ad714x, hw->start_stage,
			hw->end_stage);

	dev_dbg(ad714x->dev, "wheel %d highest_stage:%d\n", idx,
		sw->highest_stage);
}