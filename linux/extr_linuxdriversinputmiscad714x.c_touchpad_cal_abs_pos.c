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
struct ad714x_touchpad_plat {int /*<<< orphan*/  y_max_coord; int /*<<< orphan*/  y_end_stage; int /*<<< orphan*/  y_start_stage; int /*<<< orphan*/  x_max_coord; int /*<<< orphan*/  x_end_stage; int /*<<< orphan*/  x_start_stage; } ;
struct ad714x_touchpad_drv {void* y_abs_pos; void* x_abs_pos; int /*<<< orphan*/  y_highest_stage; int /*<<< orphan*/  x_highest_stage; } ;
struct ad714x_chip {int /*<<< orphan*/  dev; TYPE_2__* sw; TYPE_1__* hw; } ;
struct TYPE_4__ {struct ad714x_touchpad_drv* touchpad; } ;
struct TYPE_3__ {struct ad714x_touchpad_plat* touchpad; } ;

/* Variables and functions */
 void* ad714x_cal_abs_pos (struct ad714x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,void*,void*) ; 

__attribute__((used)) static void touchpad_cal_abs_pos(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	struct ad714x_touchpad_drv *sw = &ad714x->sw->touchpad[idx];

	sw->x_abs_pos = ad714x_cal_abs_pos(ad714x, hw->x_start_stage,
			hw->x_end_stage, sw->x_highest_stage, hw->x_max_coord);
	sw->y_abs_pos = ad714x_cal_abs_pos(ad714x, hw->y_start_stage,
			hw->y_end_stage, sw->y_highest_stage, hw->y_max_coord);

	dev_dbg(ad714x->dev, "touchpad %d absolute position:(%d, %d)\n", idx,
			sw->x_abs_pos, sw->y_abs_pos);
}