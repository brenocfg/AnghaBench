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
struct ad714x_touchpad_plat {int /*<<< orphan*/  y_end_stage; int /*<<< orphan*/  y_start_stage; int /*<<< orphan*/  x_end_stage; int /*<<< orphan*/  x_start_stage; } ;
struct ad714x_touchpad_drv {void* y_highest_stage; void* x_highest_stage; } ;
struct ad714x_chip {int /*<<< orphan*/  dev; TYPE_1__* sw; TYPE_2__* hw; } ;
struct TYPE_4__ {struct ad714x_touchpad_plat* touchpad; } ;
struct TYPE_3__ {struct ad714x_touchpad_drv* touchpad; } ;

/* Variables and functions */
 void* ad714x_cal_highest_stage (struct ad714x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,void*,void*) ; 

__attribute__((used)) static void touchpad_cal_highest_stage(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	struct ad714x_touchpad_drv *sw = &ad714x->sw->touchpad[idx];

	sw->x_highest_stage = ad714x_cal_highest_stage(ad714x,
		hw->x_start_stage, hw->x_end_stage);
	sw->y_highest_stage = ad714x_cal_highest_stage(ad714x,
		hw->y_start_stage, hw->y_end_stage);

	dev_dbg(ad714x->dev,
		"touchpad %d x_highest_stage:%d, y_highest_stage:%d\n",
		idx, sw->x_highest_stage, sw->y_highest_stage);
}