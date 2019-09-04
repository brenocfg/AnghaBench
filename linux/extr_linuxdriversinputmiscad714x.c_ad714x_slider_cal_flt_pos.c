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
struct ad714x_slider_drv {int flt_pos; int abs_pos; } ;
struct ad714x_chip {int /*<<< orphan*/  dev; TYPE_1__* sw; } ;
struct TYPE_2__ {struct ad714x_slider_drv* slider; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void ad714x_slider_cal_flt_pos(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_slider_drv *sw = &ad714x->sw->slider[idx];

	sw->flt_pos = (sw->flt_pos * (10 - 4) +
			sw->abs_pos * 4)/10;

	dev_dbg(ad714x->dev, "slider %d filter position:%d\n", idx,
		sw->flt_pos);
}