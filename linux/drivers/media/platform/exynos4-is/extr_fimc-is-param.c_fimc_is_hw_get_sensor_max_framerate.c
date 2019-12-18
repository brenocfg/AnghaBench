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
struct fimc_is {TYPE_2__* sensor; } ;
struct TYPE_4__ {TYPE_1__* drvdata; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
#define  FIMC_IS_SENSOR_ID_S5K6A3 128 

int fimc_is_hw_get_sensor_max_framerate(struct fimc_is *is)
{
	switch (is->sensor->drvdata->id) {
	case FIMC_IS_SENSOR_ID_S5K6A3:
		return 30;
	default:
		return 15;
	}
}