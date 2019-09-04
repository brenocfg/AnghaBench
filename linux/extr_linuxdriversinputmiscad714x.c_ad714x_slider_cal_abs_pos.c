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
struct ad714x_slider_plat {int /*<<< orphan*/  max_coord; int /*<<< orphan*/  end_stage; int /*<<< orphan*/  start_stage; } ;
struct ad714x_slider_drv {int /*<<< orphan*/  abs_pos; int /*<<< orphan*/  highest_stage; } ;
struct ad714x_chip {int /*<<< orphan*/  dev; TYPE_2__* sw; TYPE_1__* hw; } ;
struct TYPE_4__ {struct ad714x_slider_drv* slider; } ;
struct TYPE_3__ {struct ad714x_slider_plat* slider; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad714x_cal_abs_pos (struct ad714x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad714x_slider_cal_abs_pos(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_slider_plat *hw = &ad714x->hw->slider[idx];
	struct ad714x_slider_drv *sw = &ad714x->sw->slider[idx];

	sw->abs_pos = ad714x_cal_abs_pos(ad714x, hw->start_stage, hw->end_stage,
		sw->highest_stage, hw->max_coord);

	dev_dbg(ad714x->dev, "slider %d absolute position:%d\n", idx,
		sw->abs_pos);
}